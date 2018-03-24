/**
 * Copyright (c) 2017 TomTom N.V. All rights reserved.
 *
 * This software is the proprietary copyright of TomTom N.V. and its subsidiaries and may be used
 * for internal evaluation purposes or commercial use strictly subject to separate licensee
 * agreement between you and TomTom. If you are the licensee, you are only permitted to use
 * this Software in accordance with the terms of your license agreement. If you are not the
 * licensee then you are not authorised to use this software in any manner and should
 * immediately return it to TomTom N.V.
 */

#import <Foundation/Foundation.h>
#import <TomTomOnlineUtils/TomTomOnlineUtils.h>
#import "TTSummary.h"
#import "TTRouteLeg.h"
#import "TTRouteSection.h"
#import "TTRouteGuidance.h"

/**
 A TTFullRoute object contains parameters with information about the whole route.
 */
@interface TTFullRoute : NSObject  <TTRouteData>

/**
 TTSummary object.
 */
@property (nonatomic, readonly, strong) TTSummary *summary;

/**
 Array with route TTRouteLeg elements.
 */
@property (nonatomic, readonly, strong) NSArray<TTRouteLeg *> *legs;

/**
 Array with route TTRouteSection elements.
 */
@property (nonatomic, readonly, strong) NSArray<TTRouteSection *> *sections;

/**
 Object TTRouteGuidance.
 */
@property (nonatomic, readonly, strong) TTRouteGuidance *guidance;

/**
 Returns array of coordinates containing all elements from legs
 */
- (NSArray<NSValue *> *)fullRoute;

@end
