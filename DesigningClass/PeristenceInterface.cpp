#include <iostream>
#include <string>
#include <chrono>

struct Blob {
  Blob(const std::string &&payload_, const std::string &&path_)
	: paload(payload_),
	  path(path_) {};
  bool isEmpty() { return paload.empty(); };
  std::string paload;
  std::string path;
  std::string name;
};

class PersistenceInterface
{
  public:
	bool write(const Blob &blob);
	virtual ~PersistenceInterface() {};

  private:
	virtual bool doWrite(const Blob &blob) = 0;
};

class FileSytemPersistence : public PersistenceInterface {
  bool doWrite(const Blob &blob) override
  {
	std::cout << "doWrite\n";
	return true;
  }
};

bool PersistenceInterface::write(const Blob &blob)
{
  std::cout << "prepared to write" << "\n";
  const auto start = std::chrono::high_resolution_clock::now();
  // call virtual function
  const bool success = doWrite(blob);
  auto tm = std::chrono::high_resolution_clock::now() - start;
  std::cout << "finished writing" << "\n" << "cost "
	<< std::fixed << (double)tm.count() / 1000000000 << " ms\n";
  return success;
}

int main()
{
  Blob blob("hello", "G:/");
  FileSytemPersistence f;
  f.write(blob);
  return 0;
}
