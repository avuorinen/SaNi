#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32 || SANI_TARGET_PLATFORM == SANI_PLATFORM_WP8
#include <windows.h>
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_IOS || SANI_TARGET_PLATFORM == SANI_PLATFORM_MAC
#include <CoreFoundation/CoreFoundation.h>
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
#include <android/asset_manager.h>
#endif

#include "sani/precompiled.hpp"
#include "sani/platform/file.hpp"
#include <vector>
#include <map>
#include <map>



namespace sani {
	namespace io {

		/// @class FileSystem file_system.hpp "sani/platform/file_system.hpp"
		/// @author siquel
		/// 
		/// Helper for file access
		class FileSystem {		
		private:
			std::map<String, FILE*> handles;

		#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
			// TODO what would be the best way to initialize it?
			AAssetManager* androidAssetManager;
		#endif

		public:
			/// Default constructor
			FileSystem();
			/// Default deconstructor
			~FileSystem();

			/// Checks if the file exists
			/// @param[in] path The path where the file should be
			/// @returns true if the file exists, false if it does not exist
			bool fileExists(const String& path) const;

			/// Checks if the file is opened for reading/writing
			/// @param[in] path File path
			/// @returns true if the file is opened, false if it isn't
			bool isFileOpen(const String& path) const;

			/// Opens file for operations
			/// @param[in] path The file path
			/// @param[in] mode The mode how file should be opened
			/// @returns true if the file opening succeeded, otherwise false
			bool openFile(const String& path, const Filemode mode);

			/// Closes the file in path
			/// @param[in] path File path
			void closeFile(const String& path);

			/// Utility for checking if path is absolute path
			/// @param[in] path The path string which needs to be checked
			bool isAbsolutePath(const String& path) const;

			/// Gets the size of the file in bytes
			/// @param[in] path File path
			size_t getFileSize(const String& path) const;

			/// Reads the file into buffer
			/// @param[in] path The file path to the file
			/// @param[out] fileSize How many bytes were read
			/// @param[in] nullTerminate Should the buffer be null terminated
			unsigned char* getFileData(const String& path, size_t& fileSize, bool nullTerminate = false) const;

			/// Reads the file into string
			/// @param[in] path File path to the file
			String getFileDataString(const String& path) const;

			/// Lists the files in directory
			/// @param[out] files The files in directory
			/// @param path The path where to list files
			void listFiles(std::vector<String>& files, const String& path) const;

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
			void setAssetManager(AAssetManager* assetmanager);
#endif
		};
	}
}