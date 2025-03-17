//
//  RoomScanAPI.h
//  RoomScanAPI
//
//  Copyright (C)2025 Locometric Ltd. All Rights Reserved.
//  Your use of this file is subject to the terms and conditions.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//! Project version number for RoomScanAPI.
FOUNDATION_EXPORT double RoomScanAPIVersionNumber;

//! Project version string for RoomScanAPI.
FOUNDATION_EXPORT const unsigned char RoomScanAPIVersionString[];

/// The collection of rooms in ``RSProperty`` can also contain plots and exterior scans.
NS_SWIFT_NAME(RoomType)
typedef NS_ENUM(NSUInteger, RSRoomType) {
    /// Room
    RSRoomType_Room = 1,
    /// A plot, scanned with the PlotScan feature
    RSRoomType_Plot = 2,
    /// A scan of the walls taken from the exterior using the ExteriorScan feature
    RSRoomType_Exterior = 3
};

/// RoomScan supports several different ways of capturing a room depending on user requirements and device capabilties.
NS_SWIFT_NAME(ScanMethodType)
typedef NS_ENUM(NSUInteger, RSScanMethodType) {
    /// Scanning the room by physically holding the device against each wall in turn (this works on all Apple devices)
    RSScanMethodType_WallTouch,
    /// Scanning the room using RoomScan's ARKit-based UI (this does require LiDAR).
    RSScanMethodType_BrickMode,
    /// Apple RoomPlan (requires LiDAR).
    RSScanMethodType_RoomPlan,
    /// Draw plan manually (setting wall lengths using Bluetooth laser is supported).
    RSScanMethodType_DrawManually
};

/// The room size (displayed as a subtitle under the room name) can be shown or hidden using this property.
NS_SWIFT_NAME(RoomSizeDisplayType)
typedef NS_ENUM(NSUInteger, RSRoomSizeDisplayType) {
    /// The size is shown according to the user's selected preference (could be main dimensions, area or other attributes depending on what they have configured).
    RSRoomSizeDisplayType_Show,
    /// The size is not shown for this room, but the area is still included in the total.
    RSRoomSizeDisplayType_Hide,
    /// The size is not shown for this room and its area does not contribute to the area of the floor.
    RSRoomSizeDisplayType_Exclude
};

/// Options for wall style are provided to indicate features like balconies and outdoor areas.
NS_SWIFT_NAME(WallStyle)
typedef NS_ENUM(NSUInteger, RSWallStyle) {
    /// Standard wall style for rooms.
    RSWallStyle_Normal,
    /// Thin wall style.
    RSWallStyle_Thin,
    /// Thin and dashed line wall style.
    RSWallStyle_Broken
};

/// Export is available in a wide range of formats.
NS_SWIFT_NAME(ExportType)
typedef NS_ENUM(NSUInteger, RSExportType) {
    /// DXF with no specific units
    RSExportType_dxf,
    /// DXF with units in mm
    RSExportType_dxf_mm,
    /// DXF with units in inches
    RSExportType_dxf_inches,
    /// Floor plans in PDF
    RSExportType_pdf,
    /// Floor plans in PDF showing the area of each room
    RSExportType_pdf_room_areas,
    /// Floor plans in PDF showing all wall measurements
    RSExportType_pdf_wall_measurements,
    /// All photos in one PDF
    RSExportType_pdf_photos,
    /// Inventory of floor plan in PDF format
    RSExportType_pdf_inventory,
    /// Inventory of floor plan in CSV format
    RSExportType_csv_inventory,
    /// Metropix® format
    RSExportType_mtpix,
    /// SweetHome3D format
    RSExportType_sweethome,
    /// All photos in one ZIP organised by room
    RSExportType_zip_photos,
    /// Majesco RapidSketch format
    RSExportType_rapidsketch,
    /// Heat Loss data in CSV format
    RSExportType_csv_heatloss,
    /// Xactimate® format with the same wall thicknesses as in the RoomScan floor plan. Experimental.
    RSExportType_xactimate_thick,
    /// [Xactimate® ESX format](https://xactimate.com/)
    RSExportType_xactimate,
    /// Locometric® FML format, see [documentation](https://www.locometric.com/s/RoomScan-XML-Documentation.docx) and [sample code](https://github.com/lmetric/ParseRoomScanXML)
    RSExportType_fml_xml,
    /// [Floorplanner FML 3.0](https://floorplanner.readme.io/reference/v30-specification)
    RSExportType_fml_json,
    /// Floorplanner FML optimised for use with Symbility® CoreLogic® / Claims Connect
    RSExportType_fml_symbility,
    /// IFC format, version 4. See [specification](https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/)
    RSExportType_ifc
};

NS_SWIFT_NAME(Room)
/// The Room object represents a room, plot or exterior outline within the property. See ``RSRoomType``.
@interface RSRoom : NSObject

/// The name of the room as displayed on the floor plan
@property (retain, nonatomic) NSString * _Nonnull name;

/// The floor name that the room belongs to. Membership of a floor is defined simply by a rooms having a matching floor name, but see also ``group``.
@property (retain, nonatomic) NSString * _Nonnull floor;

/// This is a UUID stored as a string, or null if the room is not a member of a group. Rooms appear on the same floor plan diagram as other rooms in the same group. There can be more than one group on the same floor, for example, in the case of a detached annexe. Group membership is defined by having the same UUID.
@property (retain, nonatomic) NSString * _Nullable group;

/// The time and date at which the room was created. This is immutable so can be used as a unique identifier.
@property (retain, nonatomic, readonly) NSDate * _Nonnull creationDate;

/// The background colour for the room as displayed on the floor plan. This is either 4 or 2 floating point numbers in the range 0-1. If 4 numbers, it's RGBA. If 2 numbers, it's grey and alpha.
@property (retain, nonatomic) NSString * _Nonnull colour;

/// The height of the room in meters. Can be set to null, which disables wall area calculations etc.
@property (retain, nonatomic) NSNumber * _Nullable height;

/// The method that was used to scan the room, see ``RSScanMethodType``.
@property (assign, nonatomic, readonly) RSScanMethodType scanMethod;

/// The treatment of the room size, see ``RSRoomSizeDisplayType``.
@property (assign, nonatomic) RSRoomSizeDisplayType areaDisplay;

/// The drawing style for the walls, see ``RSWallStyle``.
@property (assign, nonatomic) RSWallStyle wallStyle;

/// An optional custom subtitle for the room, which appears under the room name on the plan. If present, this overrides whatever subtitle the user has configured for rooms.
@property (retain, nonatomic) NSString * _Nullable customSubtitle;

/// The answers to any custom surveys the user has completed for the room. See [RoomScan Room Surveys](https://www.locometric.com/roomscan-room-surveys).
@property (retain, nonatomic) NSDictionary *_Nullable answers;

@end

NS_SWIFT_NAME(Property)
/// The Property object represents a collection of floors, rooms, plot scans etc taken at one site.
/// This is the highest-level object in the API. Managing a collection of properties is the responsibility
/// of the host app, if required.
@interface RSProperty : NSObject

/// The first line of the address as displayed in the 'Street address' box on the Property Details screen
@property (retain, nonatomic) NSString * _Nonnull street;

/// The second line of the address as displayed in the 'Town' box on the Property Details screen
@property (retain, nonatomic) NSString * _Nonnull town;

/// The postal code of the address as displayed in the 'Postal code' box on the Property Details screen
@property (retain, nonatomic) NSString * _Nonnull postalCode;

/// The country of the address as displayed in the 'Country' box on the Property Details screen
@property (retain, nonatomic) NSString * _Nonnull country;

/// The notes relating to the property as displayed in the 'Notes' box on the Property Details screen
@property (retain, nonatomic) NSString * _Nonnull notes;

/// The rooms within the property, which also includes output from PlotScan and ExteriorScan. See ``RSRoom``.
@property (readonly) NSArray<RSRoom *> * _Nonnull rooms;

/// Before exporting in most formats, it's necessary to check none of the rooms overlap each other. This
/// function returns true if it finds any and returns the first occurrence it finds in the floor, room1 and
/// room2 parameters. The user can then be prompted to resolve the issue.
/// - Parameter floor: Returns the floor name on which the overlap occurs
/// - Parameter room1: Returns one of the names of the rooms that are overlapping
/// - Parameter room2: Returns the other of the names of the rooms that are overlapping
- (bool)findOverlappingRooms:(NSString * _Nonnull * _Nullable)floor room1:(NSString * _Nonnull * _Nullable)room1 room2:(NSString * _Nonnull * _Nullable)room2;

/// Exports the property in the specified format. The file is returned as `NSData` ready to save or send.
/// Note that you'll need to provide a suitable filename as only the data itself is returned.
/// - Parameter format: The format in which to export, see ``RSExportType``
/// - Parameter completion: A block which is called when the export is complete. If `data` is null then the export failed and the `message` parameter will contain a reason. The `message` parameter may also be non-null on success.
- (void)exportPropertyAs:(RSExportType)format completion:(void (^_Nonnull)(NSData * _Nullable data, NSString * _Nullable message))completion;

@end

NS_SWIFT_NAME(Helper)
/// The Helper object is a singleton used mainly to invoke user interface elements.
@interface RSHelper : NSObject

/// Returns the singleton ``RSHelper`` object.
+ (nonnull RSHelper *)sharedInstance;

/// Creates an empty property file and changes the current property to it.
/// - Parameter url: The URL of the property data, which must be a file URL and not already exist
- (void)createPropertyAtURL:(nonnull NSURL *)url;

/// Returns the current property. This may have been set explicitly by calling ``setProperty:`` or
/// implicitly, for example by calling ``createPropertyAtURL:``.
- (nullable RSProperty *)property;

/// Sets the property of the singleton object to the property data at the given URL. This property is used by any API call
/// that acts on a property, such as ``roomListViewController``.
/// - Parameter property: The URL of the property data, which must be a file URL and already exist
- (void)setProperty:(nonnull NSURL *)property;

/// Returns a view controller listing the rooms in the property, very similar to the list
/// of rooms screen in RoomScan Pro LiDAR. The property must first have been set using ``setProperty:``
/// or by another API call such as ``createPropertyAtURL:``. If you want the Edit, Details and Advanced Export buttons to
/// be visible, set Shows Toolbar to true on your app's navigation controller.
/// - Returns: A `UIViewController` which should be pushed onto a navigation controller with `pushViewController`
- (nonnull UIViewController *)roomListViewController;

/// Sets the colour for buttons and other highlighted text in the UI. The colour of most UI elements will be set by your app's
/// Global Accent Color Name automatically but this should change the colour of everything else from RoomScan orange.
/// - Parameter colour: The colour to apply
- (void)setAccentColour:(nonnull UIColor *)colour;

/// Provides direct access to the "New Room" screen, for apps that either don't need ``roomListViewController`` or want to
/// provide an alternative entry point to the creation of a new room.
/// - Parameters:
///   - roomName: Name of the new room, can be left blank for the user to enter
///   - floorName: Name of the floor. This is required.
///   - roomType: See ``RSRoomType``
- (nonnull UIViewController *)newRoomViewControllerWithRoomName:(nullable NSString *)roomName floor:(nonnull NSString *)floorName roomType:(RSRoomType)roomType;

/// After creating a `UIViewController` using ``newRoomViewControllerWithRoomName:floor:roomType:``, it's recommended to present
/// it to the user. Optionally, you can instead call this method to proceed directly to
/// the scan. The `UIViewController` must have been presented first but if you call ``startScan:preferredMethod:`` immediately
/// after presentation then the user won't see the New Room screen.
/// - Parameter newRoomViewController: A `UIViewController` returned from ``newRoomViewControllerWithRoomName:floor:roomType:``
/// - Parameter method: Since the New Room UI is being skipped, you are responsible for determining which method of scanning the room the user wants to use. See ``RSScanMethodType``.
- (bool)startScan:(nonnull UIViewController *)newRoomViewController preferredMethod:(RSScanMethodType)method;

@end
