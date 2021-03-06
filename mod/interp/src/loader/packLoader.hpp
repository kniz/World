#pragma once

#include "../ast/pack.hpp"
#include "packMaker.hpp"

namespace wrd {

    class packLoader : public node {
        WRD_CLASS(packLoader, node)

    public:
        packLoader(const wchar* path) : _subs(new nchain()) { _traversePack({path}); }
        packLoader(std::initializer_list<const wchar*> paths) : _subs(new nchain()) { _traversePack(paths); }
        wbool canRun(const wtypes& types) const override {
            return false;
        }

        str run(const ncontainer& args) override {
            return str();
        }

        using super::subs;
        ncontainer& subs() override {
            return *_subs;
        }

    private:
        wbool _isExcludedFile(const std::string& fileName) {
            static const std::string EXCLUDED_FILES[] = {".", ".."};
            for(std::string exclusion : EXCLUDED_FILES)
                if(fileName == exclusion)
                    return true;

            return false;
        }

        std::string _filterDirPath(const string& dirPath) {
            int last = dirPath.length() - 1;
            if(dirPath[last] == DELIMITER)
                return dirPath.substr(0, last);

            return dirPath;
        }

        void _traversePack(std::initializer_list<const wchar*> paths) {
            const std::string& cwd = fsystem::getCurrentDir();
            WRD_I("finding packs relative to %s or absolute", cwd.c_str());

            for(const wchar* path : paths) {
                WRD_I("try pack path: %s", path);

                _traversePack(std::string(path));
            }
        }

        void _traversePack(const std::string& dirPath) {
            const std::string& filtered = _filterDirPath(dirPath);
            DIR* dir = opendir(dirPath.c_str());
            if(!dir) {
                WRD_E("path %s permission denied.");
                return;
            }

            struct dirent* file = nullptr;
            while((file = readdir(dir))) {
                if(_isExcludedFile(file->d_name))
                    continue;

                // TODO: refactor to be extentiable.
                if(file->d_type == DT_DIR)
                    _traversePack(filtered + DELIMITER + file->d_name);
                else if(file->d_name == MANIFEST_FILENAME)
                    _createPack(filtered, file->d_name);
            }
        }

        void _createPack(const std::string& dirPath, const std::string& manifestName) {
            std::string manifestPath = dirPath + DELIMITER + manifestName;

            manifest mani = _interpManifest(dirPath, manifestPath);
            if(!mani.isValid()) {
                WRD_E("invalid manifest[%s] found.", manifestPath.c_str());
                return;
            }

            pack* new1 = packMaker().makeWith(mani);
            if(nul(new1)) {
                WRD_E("fail to make a pack[%s].", mani.name.c_str());
                return;
            }

            _subs->add(new1);
            _logPack(*new1);
        }

        void _logPack(const pack& pak) const {
            WRD_I("new pack [%s] has been added.", pak.getName().c_str());

            const manifest& mani = pak.getManifest();
            WRD_DI("\t.filePath=%s", mani.filePath.c_str());
            WRD_DI("\t.author=%s", mani.author.c_str());
            WRD_DI("\t.ver=%s", mani.ver.c_str());

            WRD_DI("\t.entrypoints=");
            for(const entrypoint& point : mani.points) {
                WRD_DI("\t\t.lang=%s", point.lang.c_str());
                WRD_DI("\t\t.paths=%s", point.paths[0].c_str());
            }
        }

        manifest _interpManifest(const std::string& dir, const std::string& manPath) const;

    private:
        tstr<nchain> _subs;
        static constexpr wchar DELIMITER = '/';
    };
}
