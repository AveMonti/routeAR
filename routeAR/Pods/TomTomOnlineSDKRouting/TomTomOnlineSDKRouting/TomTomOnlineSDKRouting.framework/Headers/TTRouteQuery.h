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
#import <CoreLocation/CoreLocation.h>
#import <TomTomOnlineUtils/TomTomOnlineUtils.h>


/**
 TTLocationCircle struct of circle with a center point and a radius (in meters). 
 */
typedef struct TTLocationCircle{
    CLLocationCoordinate2D centerPoint;
    double meters;
} TTLocationCircle;


/**
 Returns a TTLocationCircle struct at the given center point and a radius

 @param centerPoint center point type CLLocationCoordinate2D
 @param meters circle radius in meters
 @return TTLocationCircle
 */
NS_INLINE TTLocationCircle TTLocationCircleMake(CLLocationCoordinate2D centerPoint, double meters) {
    TTLocationCircle circle;
    circle.centerPoint = centerPoint;
    circle.meters = meters;
    return circle;
}

typedef NS_ENUM(NSInteger, TTOptionTypeRoute) {
    TTOptionTypeRouteNone,
    TTOptionTypeRouteFastest,
    TTOptionTypeRouteShortest,
    TTOptionTypeRouteEco,
    TTOptionTypeRouteThrilling
};

typedef NS_ENUM(NSInteger, TTOptionTypeAvoid){
    TTOptionTypeAvoidNone = 0,
    TTOptionTypeAvoidTollRoads = 1 << 0,
    TTOptionTypeAvoidMotorways = 1 << 1,
    TTOptionTypeAvoidFerries = 1 << 2,
    TTOptionTypeAvoidUnpavedRoads = 1 << 3,
    TTOptionTypeAvoidCarpools = 1 << 4,
    TTOptionTypeAvoidAalreadyUsedRoads = 1 << 5
};

typedef NS_ENUM(NSInteger, TTOptionInstructionsType) {
    TTOptionInstructionsTypeNone,
    TTOptionInstructionsTypeCoded,
    TTOptionInstructionsTypeText,
    TTOptionInstructionsTypeTagged
};

typedef NS_ENUM(NSInteger, TTOptionTravelMode) {
    TTOptionTravelModeNone,
    TTOptionTravelModeCar,
    TTOptionTravelModeTruck,
    TTOptionTravelModeTaxi,
    TTOptionTravelModeBus,
    TTOptionTravelModeVan,
    TTOptionTravelModeMotorCycle,
    TTOptionTravelModeBicycle,
    TTOptionTravelModePedestrian
};

typedef NS_ENUM(NSInteger, TTOptionVehicleEngineType) {
    TTOptionVehicleEngineTypeNone,
    TTOptionVehicleEngineTypeCombustion,
    TTOptionVehicleEngineTypeElectric
};

typedef NS_ENUM(NSInteger, TTOptionVehicleLoadType) {
    TTOptionVehicleLoadTypeNone,
    TTOptionVehicleLoadTypeUSHazmatClass1,
    TTOptionVehicleLoadTypeUSHazmatClass2,
    TTOptionVehicleLoadTypeUSHazmatClass3,
    TTOptionVehicleLoadTypeUSHazmatClass4,
    TTOptionVehicleLoadTypeUSHazmatClass5,
    TTOptionVehicleLoadTypeUSHazmatClass6,
    TTOptionVehicleLoadTypeUSHazmatClass7,
    TTOptionVehicleLoadTypeUSHazmatClass8,
    TTOptionVehicleLoadTypeUSHazmatClass9,
    TTOptionVehicleLoadTypeOtherHazmatExplosive,
    TTOptionVehicleLoadTypeOtherHazmatGeneral,
    TTOptionVehicleLoadTypeOtherHazmatHarmfulToWater
};

typedef NS_ENUM(NSInteger, TTOptionHilliness) {
    TTOptionHillinessNone,
    TTOptionHillinessLow,
    TTOptionHillinessNormal,
    TTOptionHillinessHigh
};

typedef NS_ENUM(NSInteger, TTOptionWindingness) {
    TTOptionWindingnessNone,
    TTOptionWindingnessLow,
    TTOptionWindingnessNormal,
    TTOptionWindingnessHigh
};

/**
 Class TTRouteQuery contains parameters needed for build query.
 */
@interface TTRouteQuery : NSObject

/**
 destPosition The map coordinate whose geographical information your destination position.
 */
@property (nonatomic, readonly, assign) CLLocationCoordinate2D origPosition;

/**
 origPosition The map coordinate whose geographical information your start position.
 */
@property (nonatomic, readonly, assign) CLLocationCoordinate2D destPosition;

/**
 wayPoints The arrray of map coordinate whose geographical information your way points
 */
@property (nonatomic, readonly, strong) NSMutableArray<NSValue *> *wayPoints;

/**
 circle with a center point and a radius (in meters). The radius must be a positive integer with the maximum value of 20050000. Note that larger integer values will not be rejected but lowered to the maximum value.
 */
@property (nonatomic, readonly, strong) NSMutableArray<NSValue *>* circles;
/**
 routeType The map coordinate whose geographical information your destination position.
 */
@property (nonatomic, readonly) TTOptionTypeRoute routeType;

/**
 isTraffic Do consider all available traffic information during routing
 */
@property (nonatomic, readonly, assign) BOOL isTraffic;

/**
 avoidType Specifies something that the route calculation should try to avoid when determining the route. Can be specified multiple times combined into bit mask.
 */
@property (nonatomic, readonly) int avoidTypeMask;

/**
 instructionsType Guidance instructions will be returned
 */
@property (nonatomic, readonly) TTOptionInstructionsType instructionsType;

/**
 language The language parameter determines the language of the guidance messages.
 */
@property (nonatomic, readonly) TTLanguage language;

/**
 departAt The date and time of departure from the origin point.
 */
@property (nonatomic, readonly, strong) NSDate* departAt;

/**
 arriveAt The date and time of arrival at the destination point.
 */
@property (nonatomic, readonly, strong) NSDate* arriveAt;

/**
 maxAlternatives Number of desired alternative routes to be calculated.
 */
@property (nonatomic, readonly, strong) NSNumber* maxAlternatives;

/**
 isComputeBestOrder The maximum allowed number of waypoints is 50, reduced to 20
 */
@property (nonatomic, readonly, assign) BOOL isComputeBestOrder;

/**
 routeRepresentation Specifies the representation of the set of routes provided as response.
 */
@property (nonatomic, readonly, strong) NSString* routeRepresentation;

/**
 travelMode The mode of travel for the requested route.
 */
@property (nonatomic, readonly) TTOptionTravelMode travelMode;

/**
 callback Specifies the jsonp callback method. Only used when contentType is jsonp.
 */
@property (nonatomic, readonly, strong) NSString* callback;

/**
 computeTravelTimeFor Specifies whether to return additional travel times using different types of traffic information (none, historic, live) as well as the default best-estimate travel time.
 */
@property (nonatomic, readonly, strong) NSString* computeTravelTimeFor;

/**
 vehicleEngineType Engine type of the vehicle. When a detailed Consumption Model is specified, it must be consistent with the value of vehicleEngineType.
 */
@property (nonatomic, readonly) TTOptionVehicleEngineType vehicleEngineType;

/**
 vehicleMaxSpeed Maximum speed of the vehicle in km/hour.
 */
@property (nonatomic, readonly, strong) NSNumber* vehicleMaxSpeed;

/**
 vehicleWeight Weight of the vehicle in kilograms.
 */
@property (nonatomic, readonly, strong) NSNumber* vehicleWeight;

/**
 vehicleAxleWeight Weight per axle of the vehicle in kg
 */
@property (nonatomic, readonly, strong) NSNumber* vehicleAxleWeight;


/**
 vehicleLength Length of the vehicle in meters.
 */
@property (nonatomic, readonly, assign) double vehicleLength;

/**
 vehicleWidth Width of the vehicle in meters.
 */
@property (nonatomic, readonly, assign) double vehicleWidth;

/**
 vehicleHeight Height of the vehicle in meters.
 */
@property (nonatomic, readonly, assign) double vehicleHeight;

/**
 isVehicleCommercial Vehicle is used for commercial purposes and thus may not be allowed to drive on some roads.
 */
@property (nonatomic, readonly, assign) BOOL isVehicleCommercial;

/**
 vehicleLoadType Types of cargo that may be classified as hazardous materials and restricted from some roads.
 */
@property (nonatomic, readonly) TTOptionVehicleLoadType vehicleLoadType;

/**
 vehicleHeading The directional heading of the vehicle in degrees starting at true North and continuing in clockwise direction.
 */
@property (nonatomic, readonly, strong) NSNumber* vehicleHeading;

/**
 hilliness Degree of hilliness for thrilling route.
 */
@property (nonatomic, readonly) TTOptionHilliness hilliness;

/**
 windingness Level of turns for thrilling route.
 */
@property (nonatomic, readonly) TTOptionWindingness windingness;

/**
 report Specifies which data should be reported for diagnosis purposes.
 */
@property (nonatomic, readonly, strong) NSString* report;


- (BOOL) isEqual:(id)object;
- (NSUInteger)hash;

@end


/**
 Class TTRouteQueryBuilder builds a query, using parameters.
 */

@interface TTRouteQueryBuilder : NSObject


@property (nonatomic, readonly, assign) CLLocationCoordinate2D origPosition;
@property (nonatomic, readonly, assign) CLLocationCoordinate2D destPosition;
@property (nonatomic, readonly, strong) NSMutableArray<NSValue *> *wayPoints;
@property (nonatomic, readonly, strong) NSMutableArray<NSValue *>* circles;
@property (nonatomic, readonly, assign) CLLocationCoordinate2D wayPoint;
@property (nonatomic, readonly) TTOptionTypeRoute routeType;
@property (nonatomic, readonly, assign) BOOL isTraffic;
@property (nonatomic, readonly) int avoidTypeMask;
@property (nonatomic, readonly) TTOptionInstructionsType instructionsType;
@property (nonatomic, readonly) TTLanguage language;
@property (nonatomic, readonly, strong) NSDate* departAt;
@property (nonatomic, readonly, strong) NSDate* arriveAt;
@property (nonatomic, readonly, strong) NSNumber* maxAlternatives;
@property (nonatomic, readonly, assign) BOOL isComputeBestOrder;
@property (nonatomic, readonly, strong) NSString* routeRepresentation;
@property (nonatomic, readonly) TTOptionTravelMode travelMode;
@property (nonatomic, readonly, strong) NSString* callback;
@property (nonatomic, readonly, strong) NSString* computeTravelTimeFor;
@property (nonatomic, readonly) TTOptionVehicleEngineType vehicleEngineType;
@property (nonatomic, readonly, strong) NSNumber* vehicleMaxSpeed;
@property (nonatomic, readonly, strong) NSNumber* vehicleWeight;
@property (nonatomic, readonly, strong) NSNumber* vehicleAxleWeight;
@property (nonatomic, readonly, assign) double vehicleLength;
@property (nonatomic, readonly, assign) double vehicleWidth;
@property (nonatomic, readonly, assign) double vehicleHeight;
@property (nonatomic, readonly, assign) BOOL isVehicleCommercial;
@property (nonatomic, readonly) TTOptionVehicleLoadType vehicleLoadType;
@property (nonatomic, readonly, strong) NSNumber* vehicleHeading;
@property (nonatomic, readonly) TTOptionHilliness hilliness;
@property (nonatomic, readonly) TTOptionWindingness windingness;
@property (nonatomic, readonly, strong) NSString* report;


/**
 @param destPosition The map coordinate whose geographical information your destination position.
 @param origPosition The map coordinate whose geographical information your start position.
 @return TTRouteQueryBuilder
 */
+ (TTRouteQueryBuilder*) createWithDest:(CLLocationCoordinate2D) destPosition andOrig:(CLLocationCoordinate2D)origPosition;

/**
 @param destPosition The map coordinate whose geographical information your destination position.
 @param origPosition The map coordinate whose geographical information your start position.
 @return id
 */
- (id)initWithDest:(CLLocationCoordinate2D)destPosition withOrig:(CLLocationCoordinate2D)origPosition;

/**
 @param wayPoints The arrray of map coordinate whose geographical information your way points
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withWayPoints:(NSArray<NSValue *>*)wayPoints;

- (TTRouteQueryBuilder*) withWayPoint:(CLLocationCoordinate2D)wayPoint;
/**
circle with a center point and a radius (in meters). The radius must be a positive integer with the maximum value of 20050000. Note that larger integer values will not be rejected but lowered to the maximum value.
 */
- (TTRouteQueryBuilder*) withCircles:(NSArray<NSValue *>*)circles;

- (TTRouteQueryBuilder*) withCircle:(struct TTLocationCircle)circle;


/**
 @param routeType The map coordinate whose geographical information your destination position.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withRouteType:(TTOptionTypeRoute)routeType;

/**
 @param isTraffic Do consider all available traffic information during routing
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withTraffic:(BOOL)isTraffic;

/**
 @param avoidType Specifies something that the route calculation should try to avoid when determining the route. Can be specified multiple times.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withAvoidType:(TTOptionTypeAvoid)avoidType;

/**
 @param instructionsType Guidance instructions will be returned
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withInstructionsType:(TTOptionInstructionsType)instructionsType;

/**
 @param language The language parameter determines the language of the guidance messages.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withLanguage:(TTLanguage)language;

/**
 @param departAt The date and time of departure from the origin point.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withDepartAt:(NSDate*)departAt;

/**
 @param arriveAt The date and time of arrival at the destination point.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withArriveAt:(NSDate*)arriveAt;

/**
 @param maxAlternatives Number of desired alternative routes to be calculated.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withMaxAlternatives:(NSNumber*)maxAlternatives;


/**
 @param isComputeBestOrder The maximum allowed number of waypoints is 50, reduced to 20
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withComputeBestOrder:(BOOL)isComputeBestOrder;


/**
 @param routeRepresentation Specifies the representation of the set of routes provided as response.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withRouteRepresentation:(NSString*)routeRepresentation;

/**
 @param travelMode The mode of travel for the requested route.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withTravelMode:(TTOptionTravelMode)travelMode;

/**
 @param callback Specifies the jsonp callback method. Only used when contentType is jsonp.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withCallback:(NSString*)callback;

/**
 @param computeTravelTimeFor Specifies whether to return additional travel times using different types of traffic information (none, historic, live) as well as the default best-estimate travel time.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withComputeTravelTimeFor:(NSString*)computeTravelTimeFor;

/**
 @param vehicleEngineType Engine type of the vehicle. When a detailed Consumption Model is specified, it must be consistent with the value of vehicleEngineType.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleEngineType:(TTOptionVehicleEngineType)vehicleEngineType;

/**
 @param vehicleMaxSpeed Maximum speed of the vehicle in km/hour.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleMaxSpeed:(NSNumber*)vehicleMaxSpeed;

/**
 @param vehicleWeight Weight of the vehicle in kilograms.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleWeight:(NSNumber*)vehicleWeight;

/**
 @param vehicleAxleWeight Weight per axle of the vehicle in kg
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleAxleWeight:(NSNumber*)vehicleAxleWeight;

/**
 @param vehicleLength Length of the vehicle in meters.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleLength:(double)vehicleLength;

/**
 @param vehicleWidth Width of the vehicle in meters.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleWidth:(double)vehicleWidth;

/**
 @param vehicleHeight Height of the vehicle in meters.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleHeight:(double)vehicleHeight;

/**
 @param isVehicleCommercial Vehicle is used for commercial purposes and thus may not be allowed to drive on some roads.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleCommercial:(BOOL)isVehicleCommercial;

/**
 @param vehicleLoadType Types of cargo that may be classified as hazardous materials and restricted from some roads.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleLoadType:(TTOptionVehicleLoadType)vehicleLoadType;

/**
 @param vehicleHeading The directional heading of the vehicle in degrees starting at true North and continuing in clockwise direction.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withVehicleHeading:(NSNumber*)vehicleHeading;

/**
 @param hilliness Degree of hilliness for thrilling route.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withHilliness:(TTOptionHilliness)hilliness;

/**
 @param windingness Level of turns for thrilling route.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withWindingness:(TTOptionWindingness)windingness;

/**
 @param report Specifies which data should be reported for diagnosis purposes.
 @return TTRouteQueryBuilder
 */
- (TTRouteQueryBuilder*) withReport:(NSString*)report;



/**
 @return TTRouteQuery
 */
- (TTRouteQuery*) build;

@end

