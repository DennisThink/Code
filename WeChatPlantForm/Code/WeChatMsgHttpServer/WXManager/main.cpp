#include "WXManager.h"
int main(int argc, char** argv) {
	std::cout << argc << argv[0] << std::endl;
	/*
	std::string strAppId = "wxc943e453bcf5b666";
	std::string strAppScrect = "020a44431b7f0853d808edb75275f14f";*/
	std::string strAppId = "wxf66d4e706af53271";
	std::string strAppScrect = "020a44431b7f0853d808edb75275f14f";
	CWXManager manager(strAppId, strAppScrect);
	manager.GetAccessToken();
	manager.GetUserList();
	manager.SendCustomerMsg();
	manager.GetUserBaseInfo();
	int x = 0;
	std::cin >> x;
    return 0;
}