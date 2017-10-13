#ifndef CollectionLayer_h
#define CollectionLayer_h

#include "Other/LayerBase/LayerBase.h"
#include "CollectionScene/Layer/ScrollViewLayer.h"

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