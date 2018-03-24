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

/**
 A TTSummary object defines summary route information between a requested start and end point.
 */
@interface TTSummary : NSObject

/**
 The route or leg length in meters.
 */
@property (nonatomic, readonly, strong) NSNumber* lengthInMeters;

/**
 Estimated travel time in seconds. Note that even when traffic=false travelTimeInSeconds still includes the delay due to traffic.
 */
@property (nonatomic, readonly, strong) NSNumber* travelTimeInSeconds;

/**
 Traffic delay is the difference between the travel time calculated using all available traffic information and travel time calculated without the influence of current and historic traffic data.
 */
@property (nonatomic, readonly, strong) NSNumber* trafficDelayInSeconds;

/**
 The estimated departure time for the route or leg. Specified as a dateTime.
 */
@property (nonatomic, readonly, strong) NSDate* departureTime;

/**
 The estimated arrival time for the route or leg. Specified as a dateTime.
 */
@property (nonatomic, readonly, strong) NSDate* arrivalTime;

/**
 Estimated travel time in seconds calculated as if there are no delays on the route due to traffic conditions (e.g. congestion). Included if requested using computeTravelTimeFor parameter.
 */
@property (nonatomic, readonly, strong) NSNumber* noTrafficTravelTimeInSeconds;

/**
 Estimated travel time in seconds calculated using time-dependent historic traffic data. Included if requested using computeTravelTimeFor parameter.
 */
@property (nonatomic, readonly, strong) NSNumber* historicTrafficTravelTimeInSeconds;

/**
 Estimated travel time in seconds calculated using real-time speed data. Included if requested using computeTravelTimeFor parameter.
 */
@property (nonatomic, readonly, strong) NSNumber* liveTrafficIncidentsTravelTimeInSeconds;

@end
