/*****************************************************************************************
*                                                                                       *
* OpenSpace                                                                             *
*                                                                                       *
* Copyright (c) 2014-2015                                                               *
*                                                                                       *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
* software and associated documentation files (the "Software"), to deal in the Software *
* without restriction, including without limitation the rights to use, copy, modify,    *
* merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
* permit persons to whom the Software is furnished to do so, subject to the following   *
* conditions:                                                                           *
*                                                                                       *
* The above copyright notice and this permission notice shall be included in all copies *
* or substantial portions of the Software.                                              *
*                                                                                       *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
****************************************************************************************/

#ifndef __ISWACONTAINER_H__
#define __ISWACONTAINER_H__
#include <openspace/rendering/renderable.h>


namespace openspace{
class ISWACygnet;
struct ExtensionFuture;

class ISWAContainer : public Renderable{
public:
	ISWAContainer(const ghoul::Dictionary& dictionary);
	~ISWAContainer();

	bool initialize() override;
	bool deinitialize() override;

	bool isReady() const override;

	virtual void render(const RenderData& data) override;
	virtual void update(const UpdateData& data) override;

	void addISWACygnet(std::string path);
	void addISWACygnet(int id);
	void addISWACygnet(std::shared_ptr<ISWACygnet> cygnet);

	void deleteCygnet(ISWACygnet* cygnet);
	void deleteCygnet(std::string name);

	std::shared_ptr<ISWACygnet> iSWACygnet(std::string name);

private:
std::vector<std::shared_ptr<ISWACygnet>> _iSWACygnets;
std::vector<std::shared_ptr<ExtensionFuture>> _extFutures;
std::vector<std::shared_ptr<ISWACygnet>> _deletedCygnets;

};	
}//namespace openspace

#endif