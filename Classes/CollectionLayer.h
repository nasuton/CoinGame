#ifndef CollectionLayer_h
#define CollectionLayer_h

#include "LayerBase.h"
#include "ScrollViewLayer.h"

class CollectionLayer : public LayerBase
{
private:
	//スクロールビューのクラス
	ScrollViewLayer* scrollViewLayer;

public:
	CollectionLayer();
	virtual ~CollectionLayer();
	
	CREATE_FUNC(CollectionLayer);
private:
	bool init();
};

#endif