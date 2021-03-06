#ifndef __FSBOX_MMF_H__
#define __FSBOX_MMF_H__

#include "Types.h"

#include <boost/iostreams/device/mapped_file.hpp>

namespace FsBox
{
// This class workarounds bugs and limitations of boost::iostreams::mapped_file
// realted to large files support
class MemoryMappedFile
{
public:
	MemoryMappedFile(size_t memViewSize = 200*64*1024); //Here we have tradoff between memory consumption and speed
	virtual ~MemoryMappedFile();

	bool Open(const std::string& fileName, stream_offset offset = 0);
	bool IsOpened() const;
	void Close();

	char* GetData();
	size_t GetDataSize() const;
	size_t GetMaxViewSize() const;

	stream_offset GetFileSize() const;
	stream_offset GetDataOffset() const;
	bool Remap(stream_offset offset);
	bool Resize(stream_offset size);
private:
	bool PeekFile(const std::string& fileName);
private:
	boost::iostreams::mapped_file _mf;
	std::string _fileName;
	stream_offset _fileOffset;
	stream_offset _fileSize;
	size_t _alignment;
	size_t _memViewSize;
};

}// namespace FsBox
#endif