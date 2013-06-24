//
//  HelloWorldLayer.m
//  iRooms
//
//  Created by Develer on 19/01/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

// Import the interfaces
#import "MainScene.h"
#import "SimpleAudioEngine.h"

@implementation MainScene

+(id) scene
{
	
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	MainScene *layer = [MainScene node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

-(void)convertRectToCocos2d:(GuiRect &)rect
{
	rect.y = fabs(rect.y - win_size.height);
}

-(void)drawImageWithPath:(string)path rect:(GuiRect)rect alpha:(int)alpha
{	
	CCSprite *img = [CCSprite spriteWithFile: [NSString stringWithUTF8String:path.c_str()]];
	img.anchorPoint = ccp(0,1);
	engine->relToAbsRect(rect);
	[self convertRectToCocos2d:rect];
	img.position = ccp(rect.x, rect.y);
	img.scaleY = rect.h / img.contentSize.height;
	img.scaleX = rect.w / img.contentSize.width;
	img.opacity = alpha;
	[self addChild: img];
}

-(void)drawText:(string)text rect:(GuiRect)rect
{
	engine->relToAbsRect(rect);
	[self convertRectToCocos2d:rect];
	int x = rect.x;
    int y = rect.y - rect.h / 2;
	// create and initialize a Label
	CCLabelTTF* label = [CCLabelTTF labelWithString:[NSString stringWithUTF8String:text.c_str()] fontName:@"Marker Felt" fontSize:14];
	
	// position the label
	label.anchorPoint = ccp(0,1);
	label.position =  ccp( x , y );
	label.color = ccc3(0, 0, 0);
	// add the label as a child to this Layer
	[self addChild: label];
}

-(void)drawRoom
{
	[self removeAllChildrenWithCleanup:true];
	GuiDataVect dv = engine->getVisibleData();
    for(GuiDataVect::iterator i = dv.begin(); i != dv.end(); ++i)
    {
        GuiData data = (*i);
        if (data.image != "")
            [self drawImageWithPath: data.image rect:data.rect alpha:data.alpha];
        if (data.text != "")
            [self drawText: data.text rect:data.rect];
    }	
}

-(void) doFrame:(ccTime)dt
{
	engine->update();
	[self drawRoom];
	[self updateMusic];
}
	


-(void)updateMusic
{
	// BGM
	std::string bgm = engine->getRoomsManager()->currentRoom()->bgm();
	if (bgm != last_bgm && bgm != "")
	{
		NSString *sound_name = [NSString stringWithCString:bgm.c_str()];
		NSString *fullpath = [[NSBundle mainBundle] pathForResource:sound_name ofType:@""];
		
		[[SimpleAudioEngine sharedEngine] playBackgroundMusic:fullpath loop:true];
		[[SimpleAudioEngine sharedEngine] setBackgroundMusicVolume: 0.5f];
		last_bgm = bgm;
	}
	if (bgm == "") [[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
	
	// SFX
	std::vector<std::string>sfx = engine->getSFX();
	for (std::vector<std::string>::iterator i = sfx.begin(); i != sfx.end(); ++i)
	{
		NSString *sound_name = [NSString stringWithCString:(*i).c_str()];
		NSString *fullpath = [[NSBundle mainBundle] pathForResource:sound_name ofType:@""];
		[[SimpleAudioEngine sharedEngine] playEffect: fullpath];
	}
		
}

// on "init" you need to initialize your instance
-(id) init
{

	// always call "super" init
	// Apple recommends to re-assign "self" with the "super" return value
	if( (self=[super init] )) {
		// Init the engine
		engine = new Engine;
		NSString *fullpath = [[NSBundle mainBundle] pathForResource:@"world" ofType:@"rooms"];
		engine->loadWorldFromFile([fullpath UTF8String]);
		// ask director the the window size
		win_size = [[CCDirector sharedDirector] winSize];
		engine->getRoomsManager()->setRoomSize(win_size.width, win_size.height);
		
		[SimpleAudioEngine sharedEngine];
		
		self.isTouchEnabled = YES;
		
		// schedule a repeating callback on every frame
		[self schedule:@selector(doFrame:)];
	}
	return self;
}

-(void) registerWithTouchDispatcher
{
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:0 swallowsTouches:YES];
}

- (BOOL)ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event {
    return YES;
}

- (void)ccTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event {
	CGPoint location = [self convertTouchToNodeSpace: touch];
	
	GuiRect point(location.x, location.y, 0, 0);
	[self convertRectToCocos2d:point];
	std::pair<float, float> coord = engine->absToRelCoord(point.x, point.y);
	engine->click(coord.first, coord.second);
}

// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
	// in case you have something to dealloc, do it in this method
	// in this particular example nothing needs to be released.
	// cocos2d will automatically release all the children (Label)
	
	delete engine;
	
	// don't forget to call "super dealloc"
	[super dealloc];
}

@end
