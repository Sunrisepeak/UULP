#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SCREEN (std::cout)

class More {
public:	    // Big Five
    
    More(std::string filename, int ps = 10) : pageSize { ps }, ifs( filename ) { }
    
    More(const More &) = delete;
    
    More(const More &&) = delete;
    
    More & operator=(const More &) = delete;
    
    More & operator=(const More &&) = delete;

    ~More() { ifs.close(); }

public:	    // member function

    bool empty() const { return ifs.eof(); } 

    std::string getNextLine() {
	if (empty()) return "";

	std::string line;
	std::getline(ifs, line);
	return line + '\n';
    }

    std::string getNextPage() {
	std::string page;
	for (int i = 0; !empty() && i < pageSize; i++)
	    page += getNextLine();
	return page;
    }

    bool reset(const std::string &filename) {
	if (ifs.is_open()) ifs.close();
	ifs.open(filename);
	return ifs.is_open();
    }

private:    // data member
    int pageSize;
    std::ifstream ifs;
};

int getCmd() {
    //printf("\033[7m more? \033[m");
    return std::cin.get();
}

int main(int argc, char **argv) {
    if (argc == 1) {
	SCREEN << "not implement" << std::endl;
	return -1;
    }
    More myMore(argv[1]);
    SCREEN << myMore.getNextPage();

    int cmd;	// Note use int not char [for cin.get]
    while (!myMore.empty() && (cmd = getCmd()) != 'q') {
	switch (cmd) { 
	    case ' ' : SCREEN << myMore.getNextPage(); break;
	    case '\n': SCREEN << myMore.getNextLine(); break;
            case 'h' :
	    case 'H' : SCREEN << "No Help.." << std::endl; break;
	}
    }
    return 0;
}
