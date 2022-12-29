#include "File.h"

File::File(char *fileName, char *mode, bool bin) :
  fileName(fileName), mode(mode), 
  bin(bin), buffSize(0), buff(NULL),
  buffStep(50)
{
  if (bin)
    mode += 'b';
  file = fopen(fileName, mode);
  /*  if (file == NULL)
      throw FileOpeningFailure(fileName);*/
}

File::~File()
{
  if (file)
    fclose(file);
  file = NULL;
}

size_t File::read(buffer_t buff, size_t size)
{
  /*  if (buff == NULL)
      throw NullPointerException();*/
  return fread(buff, 1, size, file);
}

bool File::write(buffer_t buff, size_t size)
{
  return fwrite(buff, 1, size, file) != 0;
}

char *File::readLine(){
  int size = 0;
  char c;
  while (((c = next()) != '\n') && c != 0) {
    if (size >= buffSize - 1){
      buffSize += buffStep;
      char *tmpBuff = new char[buffSize];
      for (int i = 0; i < size - 2; i++)
	  tmpBuff[i] = buff[i];
      delete[] buff;
      buff = tmpBuff;
    }
    buff[size] = c;
    size++;
  }
  if (size==0 && c == 0)
    return NULL;
  buff[size] = '\0';
  return buff;
}

bool File::setFip(fip_t fip)
{
  return fseek(file, fip, SEEK_SET) != -1;
}

fip_t File::getFip()
{ 
  return ftell(file);
}

char File::next()
{
  char c = 0;
  read((unsigned char *)&c, 1);
  return c;
}



