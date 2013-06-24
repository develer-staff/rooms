//
//  HelloWorldLayer.h
//  iRooms
//
//  Created by Develer on 19/01/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//


// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"
#import "engine.h"

// HelloWorld Layer
@interface MainScene : CCLayer
{
	Engine *engine;
	CGSize win_size;
	std::string last_bgm;
}

// returns a Scene that contains the HelloWorld as the only child
+(id) scene;

@end
