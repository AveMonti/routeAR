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
#import <boost/bind.hpp>
#import "TTFullRoute.h"

#include "RouteResult.h"
#include "Route.h"
#include "FullRoute.h"

@interface TTRouteParser : NSObject

+ (NSArray<TTFullRoute *>*)parseResponse:(std::shared_ptr<RouteResponse>)response;
+ (NSArray<TTRouteSection *> *)vecToListSection:(std::vector<std::shared_ptr<RouteSection>>)vect;
+ (NSArray<TTRouteLeg *>*)vecToListLeg:(std::vector<std::shared_ptr<RouteLeg>>)vect;

@end

