//
//  iRoomsAppDelegate.h
//  iRooms
//
//  Created by Develer on 19/01/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "engine.h"

@class RootViewController;

@interface iRoomsAppDelegate : NSObject <UIApplicationDelegate> {
	UIWindow			*window;
	RootViewController	*viewController;
	Engine *engine;
}

@property (nonatomic, retain) UIWindow *window;

@end
