/*
 * @Description: 
 * @Author: kai
 * @Date: 2021-02-24 16:34:32
 * @LastEditors: kai
 * @LastEditTime: 2021-02-24 16:38:37
 */
#include <vector>
template <class T> class std::vector;
#define SOAP_NAMESPACE_OF_MAC	"http://machine.webService.workHelper.cnki.com/"
//gsoap MAC   schema namespace:	http://machine.webService.workHelper.cnki.com/
//gsoap MAC   schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Forward Declarations                                                       *
 *                                                                            *
\******************************************************************************/


class MAC__fetchRobotConfig;

class MAC__fetchRobotConfigResponse;

class MAC__GetLineServerInfo;

class MAC__GetLineServerInfoResponse;

class MAC__addRobotRunState;

class MAC__addRobotRunStateResponse;

class MAC__GetLineServerList;

class MAC__GetLineServerListResponse;

class MAC__GetServerInfo;

class MAC__GetServerInfoResponse;


/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   http://machine.webService.workHelper.cnki.com/                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   http://machine.webService.workHelper.cnki.com/                           *
 *                                                                            *
\******************************************************************************/

/// @brief "http://machine.webService.workHelper.cnki.com/":fetchRobotConfig is a complexType.
///
/// @note class MAC__fetchRobotConfig operations:
/// - MAC__fetchRobotConfig* soap_new_MAC__fetchRobotConfig(soap*) allocate and default initialize
/// - MAC__fetchRobotConfig* soap_new_MAC__fetchRobotConfig(soap*, int num) allocate and default initialize an array
/// - MAC__fetchRobotConfig* soap_new_req_MAC__fetchRobotConfig(soap*, ...) allocate, set required members
/// - MAC__fetchRobotConfig* soap_new_set_MAC__fetchRobotConfig(soap*, ...) allocate, set all public members
/// - MAC__fetchRobotConfig::soap_default(soap*) default initialize members
/// - int soap_read_MAC__fetchRobotConfig(soap*, MAC__fetchRobotConfig*) deserialize from a stream
/// - int soap_write_MAC__fetchRobotConfig(soap*, MAC__fetchRobotConfig*) serialize to a stream
/// - MAC__fetchRobotConfig* MAC__fetchRobotConfig::soap_dup(soap*) returns deep copy of MAC__fetchRobotConfig, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__fetchRobotConfig::soap_del() deep deletes MAC__fetchRobotConfig data members, use only after MAC__fetchRobotConfig::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__fetchRobotConfig::soap_type() returns SOAP_TYPE_MAC__fetchRobotConfig or derived type identifier
class MAC__fetchRobotConfig
{ public:
/// Element "token" of type xs:string.
    wchar_t*                             token                          0;	///< Optional element.
/// Element "managerIP" of type xs:string.
    wchar_t*                             managerIP                      0;	///< Optional element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":fetchRobotConfigResponse is a complexType.
///
/// @note class MAC__fetchRobotConfigResponse operations:
/// - MAC__fetchRobotConfigResponse* soap_new_MAC__fetchRobotConfigResponse(soap*) allocate and default initialize
/// - MAC__fetchRobotConfigResponse* soap_new_MAC__fetchRobotConfigResponse(soap*, int num) allocate and default initialize an array
/// - MAC__fetchRobotConfigResponse* soap_new_req_MAC__fetchRobotConfigResponse(soap*, ...) allocate, set required members
/// - MAC__fetchRobotConfigResponse* soap_new_set_MAC__fetchRobotConfigResponse(soap*, ...) allocate, set all public members
/// - MAC__fetchRobotConfigResponse::soap_default(soap*) default initialize members
/// - int soap_read_MAC__fetchRobotConfigResponse(soap*, MAC__fetchRobotConfigResponse*) deserialize from a stream
/// - int soap_write_MAC__fetchRobotConfigResponse(soap*, MAC__fetchRobotConfigResponse*) serialize to a stream
/// - MAC__fetchRobotConfigResponse* MAC__fetchRobotConfigResponse::soap_dup(soap*) returns deep copy of MAC__fetchRobotConfigResponse, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__fetchRobotConfigResponse::soap_del() deep deletes MAC__fetchRobotConfigResponse data members, use only after MAC__fetchRobotConfigResponse::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__fetchRobotConfigResponse::soap_type() returns SOAP_TYPE_MAC__fetchRobotConfigResponse or derived type identifier
class MAC__fetchRobotConfigResponse
{ public:
/// Element "return" of type xs:string.
    wchar_t*                             return_                        0;	///< Optional element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":GetLineServerInfo is a complexType.
///
/// @note class MAC__GetLineServerInfo operations:
/// - MAC__GetLineServerInfo* soap_new_MAC__GetLineServerInfo(soap*) allocate and default initialize
/// - MAC__GetLineServerInfo* soap_new_MAC__GetLineServerInfo(soap*, int num) allocate and default initialize an array
/// - MAC__GetLineServerInfo* soap_new_req_MAC__GetLineServerInfo(soap*, ...) allocate, set required members
/// - MAC__GetLineServerInfo* soap_new_set_MAC__GetLineServerInfo(soap*, ...) allocate, set all public members
/// - MAC__GetLineServerInfo::soap_default(soap*) default initialize members
/// - int soap_read_MAC__GetLineServerInfo(soap*, MAC__GetLineServerInfo*) deserialize from a stream
/// - int soap_write_MAC__GetLineServerInfo(soap*, MAC__GetLineServerInfo*) serialize to a stream
/// - MAC__GetLineServerInfo* MAC__GetLineServerInfo::soap_dup(soap*) returns deep copy of MAC__GetLineServerInfo, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__GetLineServerInfo::soap_del() deep deletes MAC__GetLineServerInfo data members, use only after MAC__GetLineServerInfo::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__GetLineServerInfo::soap_type() returns SOAP_TYPE_MAC__GetLineServerInfo or derived type identifier
class MAC__GetLineServerInfo
{ public:
/// Element "token" of type xs:string.
    wchar_t*                             token                          0;	///< Optional element.
/// Element "lineId" of type xs:int.
    int                                  lineId                         1;	///< Required element.
/// Element "outUse" of type xs:boolean.
    bool                                 outUse                         1;	///< Required element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":GetLineServerInfoResponse is a complexType.
///
/// @note class MAC__GetLineServerInfoResponse operations:
/// - MAC__GetLineServerInfoResponse* soap_new_MAC__GetLineServerInfoResponse(soap*) allocate and default initialize
/// - MAC__GetLineServerInfoResponse* soap_new_MAC__GetLineServerInfoResponse(soap*, int num) allocate and default initialize an array
/// - MAC__GetLineServerInfoResponse* soap_new_req_MAC__GetLineServerInfoResponse(soap*, ...) allocate, set required members
/// - MAC__GetLineServerInfoResponse* soap_new_set_MAC__GetLineServerInfoResponse(soap*, ...) allocate, set all public members
/// - MAC__GetLineServerInfoResponse::soap_default(soap*) default initialize members
/// - int soap_read_MAC__GetLineServerInfoResponse(soap*, MAC__GetLineServerInfoResponse*) deserialize from a stream
/// - int soap_write_MAC__GetLineServerInfoResponse(soap*, MAC__GetLineServerInfoResponse*) serialize to a stream
/// - MAC__GetLineServerInfoResponse* MAC__GetLineServerInfoResponse::soap_dup(soap*) returns deep copy of MAC__GetLineServerInfoResponse, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__GetLineServerInfoResponse::soap_del() deep deletes MAC__GetLineServerInfoResponse data members, use only after MAC__GetLineServerInfoResponse::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__GetLineServerInfoResponse::soap_type() returns SOAP_TYPE_MAC__GetLineServerInfoResponse or derived type identifier
class MAC__GetLineServerInfoResponse
{ public:
/// Element "return" of type xs:string.
    wchar_t*                             return_                        0;	///< Optional element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":addRobotRunState is a complexType.
///
/// @note class MAC__addRobotRunState operations:
/// - MAC__addRobotRunState* soap_new_MAC__addRobotRunState(soap*) allocate and default initialize
/// - MAC__addRobotRunState* soap_new_MAC__addRobotRunState(soap*, int num) allocate and default initialize an array
/// - MAC__addRobotRunState* soap_new_req_MAC__addRobotRunState(soap*, ...) allocate, set required members
/// - MAC__addRobotRunState* soap_new_set_MAC__addRobotRunState(soap*, ...) allocate, set all public members
/// - MAC__addRobotRunState::soap_default(soap*) default initialize members
/// - int soap_read_MAC__addRobotRunState(soap*, MAC__addRobotRunState*) deserialize from a stream
/// - int soap_write_MAC__addRobotRunState(soap*, MAC__addRobotRunState*) serialize to a stream
/// - MAC__addRobotRunState* MAC__addRobotRunState::soap_dup(soap*) returns deep copy of MAC__addRobotRunState, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__addRobotRunState::soap_del() deep deletes MAC__addRobotRunState data members, use only after MAC__addRobotRunState::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__addRobotRunState::soap_type() returns SOAP_TYPE_MAC__addRobotRunState or derived type identifier
class MAC__addRobotRunState
{ public:
/// Element "token" of type xs:string.
    wchar_t*                             token                          0;	///< Optional element.
/// Element "managerIP" of type xs:string.
    wchar_t*                             managerIP                      0;	///< Optional element.
/// Element "LineId" of type xs:int.
    int                                  LineId                         1;	///< Required element.
/// Element "PostId" of type xs:int.
    int                                  PostId                         1;	///< Required element.
/// Element "runningNum" of type xs:int.
    int                                  runningNum                     1;	///< Required element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":addRobotRunStateResponse is a complexType.
///
/// @note class MAC__addRobotRunStateResponse operations:
/// - MAC__addRobotRunStateResponse* soap_new_MAC__addRobotRunStateResponse(soap*) allocate and default initialize
/// - MAC__addRobotRunStateResponse* soap_new_MAC__addRobotRunStateResponse(soap*, int num) allocate and default initialize an array
/// - MAC__addRobotRunStateResponse* soap_new_req_MAC__addRobotRunStateResponse(soap*, ...) allocate, set required members
/// - MAC__addRobotRunStateResponse* soap_new_set_MAC__addRobotRunStateResponse(soap*, ...) allocate, set all public members
/// - MAC__addRobotRunStateResponse::soap_default(soap*) default initialize members
/// - int soap_read_MAC__addRobotRunStateResponse(soap*, MAC__addRobotRunStateResponse*) deserialize from a stream
/// - int soap_write_MAC__addRobotRunStateResponse(soap*, MAC__addRobotRunStateResponse*) serialize to a stream
/// - MAC__addRobotRunStateResponse* MAC__addRobotRunStateResponse::soap_dup(soap*) returns deep copy of MAC__addRobotRunStateResponse, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__addRobotRunStateResponse::soap_del() deep deletes MAC__addRobotRunStateResponse data members, use only after MAC__addRobotRunStateResponse::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__addRobotRunStateResponse::soap_type() returns SOAP_TYPE_MAC__addRobotRunStateResponse or derived type identifier
class MAC__addRobotRunStateResponse
{ public:
/// Element "return" of type xs:string.
    wchar_t*                             return_                        0;	///< Optional element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":GetLineServerList is a complexType.
///
/// @note class MAC__GetLineServerList operations:
/// - MAC__GetLineServerList* soap_new_MAC__GetLineServerList(soap*) allocate and default initialize
/// - MAC__GetLineServerList* soap_new_MAC__GetLineServerList(soap*, int num) allocate and default initialize an array
/// - MAC__GetLineServerList* soap_new_req_MAC__GetLineServerList(soap*, ...) allocate, set required members
/// - MAC__GetLineServerList* soap_new_set_MAC__GetLineServerList(soap*, ...) allocate, set all public members
/// - MAC__GetLineServerList::soap_default(soap*) default initialize members
/// - int soap_read_MAC__GetLineServerList(soap*, MAC__GetLineServerList*) deserialize from a stream
/// - int soap_write_MAC__GetLineServerList(soap*, MAC__GetLineServerList*) serialize to a stream
/// - MAC__GetLineServerList* MAC__GetLineServerList::soap_dup(soap*) returns deep copy of MAC__GetLineServerList, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__GetLineServerList::soap_del() deep deletes MAC__GetLineServerList data members, use only after MAC__GetLineServerList::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__GetLineServerList::soap_type() returns SOAP_TYPE_MAC__GetLineServerList or derived type identifier
class MAC__GetLineServerList
{ public:
/// Element "outUse" of type xs:boolean.
    bool                                 outUse                         1;	///< Required element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":GetLineServerListResponse is a complexType.
///
/// @note class MAC__GetLineServerListResponse operations:
/// - MAC__GetLineServerListResponse* soap_new_MAC__GetLineServerListResponse(soap*) allocate and default initialize
/// - MAC__GetLineServerListResponse* soap_new_MAC__GetLineServerListResponse(soap*, int num) allocate and default initialize an array
/// - MAC__GetLineServerListResponse* soap_new_req_MAC__GetLineServerListResponse(soap*, ...) allocate, set required members
/// - MAC__GetLineServerListResponse* soap_new_set_MAC__GetLineServerListResponse(soap*, ...) allocate, set all public members
/// - MAC__GetLineServerListResponse::soap_default(soap*) default initialize members
/// - int soap_read_MAC__GetLineServerListResponse(soap*, MAC__GetLineServerListResponse*) deserialize from a stream
/// - int soap_write_MAC__GetLineServerListResponse(soap*, MAC__GetLineServerListResponse*) serialize to a stream
/// - MAC__GetLineServerListResponse* MAC__GetLineServerListResponse::soap_dup(soap*) returns deep copy of MAC__GetLineServerListResponse, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__GetLineServerListResponse::soap_del() deep deletes MAC__GetLineServerListResponse data members, use only after MAC__GetLineServerListResponse::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__GetLineServerListResponse::soap_type() returns SOAP_TYPE_MAC__GetLineServerListResponse or derived type identifier
class MAC__GetLineServerListResponse
{ public:
/// Element "return" of type xs:string.
    wchar_t*                             return_                        0;	///< Optional element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":GetServerInfo is a complexType.
///
/// @note class MAC__GetServerInfo operations:
/// - MAC__GetServerInfo* soap_new_MAC__GetServerInfo(soap*) allocate and default initialize
/// - MAC__GetServerInfo* soap_new_MAC__GetServerInfo(soap*, int num) allocate and default initialize an array
/// - MAC__GetServerInfo* soap_new_req_MAC__GetServerInfo(soap*, ...) allocate, set required members
/// - MAC__GetServerInfo* soap_new_set_MAC__GetServerInfo(soap*, ...) allocate, set all public members
/// - MAC__GetServerInfo::soap_default(soap*) default initialize members
/// - int soap_read_MAC__GetServerInfo(soap*, MAC__GetServerInfo*) deserialize from a stream
/// - int soap_write_MAC__GetServerInfo(soap*, MAC__GetServerInfo*) serialize to a stream
/// - MAC__GetServerInfo* MAC__GetServerInfo::soap_dup(soap*) returns deep copy of MAC__GetServerInfo, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__GetServerInfo::soap_del() deep deletes MAC__GetServerInfo data members, use only after MAC__GetServerInfo::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__GetServerInfo::soap_type() returns SOAP_TYPE_MAC__GetServerInfo or derived type identifier
class MAC__GetServerInfo
{ public:
/// Element "serverId" of type xs:int.
    int                                  serverId                       1;	///< Required element.
/// Element "postId" of type xs:int.
    int                                  postId                         1;	///< Required element.
/// Element "outUse" of type xs:boolean.
    bool                                 outUse                         1;	///< Required element.
/// Element "isSync" of type xs:boolean.
    bool                                 isSync                         1;	///< Required element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};

/// @brief "http://machine.webService.workHelper.cnki.com/":GetServerInfoResponse is a complexType.
///
/// @note class MAC__GetServerInfoResponse operations:
/// - MAC__GetServerInfoResponse* soap_new_MAC__GetServerInfoResponse(soap*) allocate and default initialize
/// - MAC__GetServerInfoResponse* soap_new_MAC__GetServerInfoResponse(soap*, int num) allocate and default initialize an array
/// - MAC__GetServerInfoResponse* soap_new_req_MAC__GetServerInfoResponse(soap*, ...) allocate, set required members
/// - MAC__GetServerInfoResponse* soap_new_set_MAC__GetServerInfoResponse(soap*, ...) allocate, set all public members
/// - MAC__GetServerInfoResponse::soap_default(soap*) default initialize members
/// - int soap_read_MAC__GetServerInfoResponse(soap*, MAC__GetServerInfoResponse*) deserialize from a stream
/// - int soap_write_MAC__GetServerInfoResponse(soap*, MAC__GetServerInfoResponse*) serialize to a stream
/// - MAC__GetServerInfoResponse* MAC__GetServerInfoResponse::soap_dup(soap*) returns deep copy of MAC__GetServerInfoResponse, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - MAC__GetServerInfoResponse::soap_del() deep deletes MAC__GetServerInfoResponse data members, use only after MAC__GetServerInfoResponse::soap_dup(NULL) (use soapcpp2 -Ed)
/// - int MAC__GetServerInfoResponse::soap_type() returns SOAP_TYPE_MAC__GetServerInfoResponse or derived type identifier
class MAC__GetServerInfoResponse
{ public:
/// Element "return" of type xs:string.
    wchar_t*                             return_                        0;	///< Optional element.
/// Pointer to soap context that manages this instance.
    struct soap                         *soap                          ;
};


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   http://machine.webService.workHelper.cnki.com/                           *
 *                                                                            *
\******************************************************************************/

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":fetchRobotConfig of type "http://machine.webService.workHelper.cnki.com/":fetchRobotConfig.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":fetchRobotConfigResponse of type "http://machine.webService.workHelper.cnki.com/":fetchRobotConfigResponse.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":GetLineServerInfo of type "http://machine.webService.workHelper.cnki.com/":GetLineServerInfo.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":GetLineServerInfoResponse of type "http://machine.webService.workHelper.cnki.com/":GetLineServerInfoResponse.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":addRobotRunState of type "http://machine.webService.workHelper.cnki.com/":addRobotRunState.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":addRobotRunStateResponse of type "http://machine.webService.workHelper.cnki.com/":addRobotRunStateResponse.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":GetLineServerList of type "http://machine.webService.workHelper.cnki.com/":GetLineServerList.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":GetLineServerListResponse of type "http://machine.webService.workHelper.cnki.com/":GetLineServerListResponse.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":GetServerInfo of type "http://machine.webService.workHelper.cnki.com/":GetServerInfo.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.

/// @brief Top-level root element "http://machine.webService.workHelper.cnki.com/":GetServerInfoResponse of type "http://machine.webService.workHelper.cnki.com/":GetServerInfoResponse.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration.


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   http://machine.webService.workHelper.cnki.com/                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap MAC  service name:	MachineWSServiceImplServiceSoapBinding 
//gsoap MAC  service type:	IMachineWSService 
//gsoap MAC  service port:	http://218.26.30.70:9090/WorkHelper/ws/machineWSService 
//gsoap MAC  service namespace:	http://machine.webService.workHelper.cnki.com/ 
//gsoap MAC  service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage MachineWSServiceImplService Definitions

@section MachineWSServiceImplService_bindings Service Bindings

  - @ref MachineWSServiceImplServiceSoapBinding

@section MachineWSServiceImplService_more More Information

  - @ref page_notes "Notes"

  - @ref page_XMLDataBinding "XML Data Binding"

  - @ref SOAP_ENV__Header "SOAP Header Content" (when applicable)

  - @ref SOAP_ENV__Detail "SOAP Fault Detail Content" (when applicable)


*/

/** @page MachineWSServiceImplServiceSoapBinding Binding "MachineWSServiceImplServiceSoapBinding"

@section MachineWSServiceImplServiceSoapBinding_operations Operations of Binding "MachineWSServiceImplServiceSoapBinding"

  - @ref __MAC__fetchRobotConfig

  - @ref __MAC__GetLineServerInfo

  - @ref __MAC__addRobotRunState

  - @ref __MAC__GetLineServerList

  - @ref __MAC__GetServerInfo

@section MachineWSServiceImplServiceSoapBinding_ports Default endpoints of Binding "MachineWSServiceImplServiceSoapBinding"

  - http://218.26.30.70:9090/WorkHelper/ws/machineWSService


*/

/******************************************************************************\
 *                                                                            *
 * Service Binding                                                            *
 *   MachineWSServiceImplServiceSoapBinding                                   *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   __MAC__fetchRobotConfig                                                  *
 *                                                                            *
\******************************************************************************/


/** Operation "__MAC__fetchRobotConfig" of service binding "MachineWSServiceImplServiceSoapBinding".

  - SOAP document/literal style messaging

  - Default endpoints:
    - http://218.26.30.70:9090/WorkHelper/ws/machineWSService

  - Addressing input action: ""

  - Addressing output action: "Response"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call___MAC__fetchRobotConfig(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    MAC__fetchRobotConfig*              MAC__fetchRobotConfig_,
    // output parameters:
    MAC__fetchRobotConfigResponse      &MAC__fetchRobotConfigResponse_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int __MAC__fetchRobotConfig(
    struct soap *soap,
    // input parameters:
    MAC__fetchRobotConfig*              MAC__fetchRobotConfig_,
    // output parameters:
    MAC__fetchRobotConfigResponse      &MAC__fetchRobotConfigResponse_
  );
@endcode

C++ proxy class (defined in soapMachineWSServiceImplServiceSoapBindingProxy.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapMachineWSServiceImplServiceSoapBindingService.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap MAC  service method-protocol:	fetchRobotConfig SOAP
//gsoap MAC  service method-style:	fetchRobotConfig document
//gsoap MAC  service method-encoding:	fetchRobotConfig literal
//gsoap MAC  service method-action:	fetchRobotConfig ""
//gsoap MAC  service method-output-action:	fetchRobotConfig Response
int __MAC__fetchRobotConfig(
    MAC__fetchRobotConfig*              MAC__fetchRobotConfig_,	///< Input parameter
    MAC__fetchRobotConfigResponse      &MAC__fetchRobotConfigResponse_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   __MAC__GetLineServerInfo                                                 *
 *                                                                            *
\******************************************************************************/


/** Operation "__MAC__GetLineServerInfo" of service binding "MachineWSServiceImplServiceSoapBinding".

  - SOAP document/literal style messaging

  - Default endpoints:
    - http://218.26.30.70:9090/WorkHelper/ws/machineWSService

  - Addressing input action: ""

  - Addressing output action: "Response"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call___MAC__GetLineServerInfo(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    MAC__GetLineServerInfo*             MAC__GetLineServerInfo_,
    // output parameters:
    MAC__GetLineServerInfoResponse     &MAC__GetLineServerInfoResponse_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int __MAC__GetLineServerInfo(
    struct soap *soap,
    // input parameters:
    MAC__GetLineServerInfo*             MAC__GetLineServerInfo_,
    // output parameters:
    MAC__GetLineServerInfoResponse     &MAC__GetLineServerInfoResponse_
  );
@endcode

C++ proxy class (defined in soapMachineWSServiceImplServiceSoapBindingProxy.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapMachineWSServiceImplServiceSoapBindingService.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap MAC  service method-protocol:	GetLineServerInfo SOAP
//gsoap MAC  service method-style:	GetLineServerInfo document
//gsoap MAC  service method-encoding:	GetLineServerInfo literal
//gsoap MAC  service method-action:	GetLineServerInfo ""
//gsoap MAC  service method-output-action:	GetLineServerInfo Response
int __MAC__GetLineServerInfo(
    MAC__GetLineServerInfo*             MAC__GetLineServerInfo_,	///< Input parameter
    MAC__GetLineServerInfoResponse     &MAC__GetLineServerInfoResponse_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   __MAC__addRobotRunState                                                  *
 *                                                                            *
\******************************************************************************/


/** Operation "__MAC__addRobotRunState" of service binding "MachineWSServiceImplServiceSoapBinding".

  - SOAP document/literal style messaging

  - Default endpoints:
    - http://218.26.30.70:9090/WorkHelper/ws/machineWSService

  - Addressing input action: ""

  - Addressing output action: "Response"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call___MAC__addRobotRunState(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    MAC__addRobotRunState*              MAC__addRobotRunState_,
    // output parameters:
    MAC__addRobotRunStateResponse      &MAC__addRobotRunStateResponse_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int __MAC__addRobotRunState(
    struct soap *soap,
    // input parameters:
    MAC__addRobotRunState*              MAC__addRobotRunState_,
    // output parameters:
    MAC__addRobotRunStateResponse      &MAC__addRobotRunStateResponse_
  );
@endcode

C++ proxy class (defined in soapMachineWSServiceImplServiceSoapBindingProxy.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapMachineWSServiceImplServiceSoapBindingService.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap MAC  service method-protocol:	addRobotRunState SOAP
//gsoap MAC  service method-style:	addRobotRunState document
//gsoap MAC  service method-encoding:	addRobotRunState literal
//gsoap MAC  service method-action:	addRobotRunState ""
//gsoap MAC  service method-output-action:	addRobotRunState Response
int __MAC__addRobotRunState(
    MAC__addRobotRunState*              MAC__addRobotRunState_,	///< Input parameter
    MAC__addRobotRunStateResponse      &MAC__addRobotRunStateResponse_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   __MAC__GetLineServerList                                                 *
 *                                                                            *
\******************************************************************************/


/** Operation "__MAC__GetLineServerList" of service binding "MachineWSServiceImplServiceSoapBinding".

  - SOAP document/literal style messaging

  - Default endpoints:
    - http://218.26.30.70:9090/WorkHelper/ws/machineWSService

  - Addressing input action: ""

  - Addressing output action: "Response"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call___MAC__GetLineServerList(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    MAC__GetLineServerList*             MAC__GetLineServerList_,
    // output parameters:
    MAC__GetLineServerListResponse     &MAC__GetLineServerListResponse_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int __MAC__GetLineServerList(
    struct soap *soap,
    // input parameters:
    MAC__GetLineServerList*             MAC__GetLineServerList_,
    // output parameters:
    MAC__GetLineServerListResponse     &MAC__GetLineServerListResponse_
  );
@endcode

C++ proxy class (defined in soapMachineWSServiceImplServiceSoapBindingProxy.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapMachineWSServiceImplServiceSoapBindingService.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap MAC  service method-protocol:	GetLineServerList SOAP
//gsoap MAC  service method-style:	GetLineServerList document
//gsoap MAC  service method-encoding:	GetLineServerList literal
//gsoap MAC  service method-action:	GetLineServerList ""
//gsoap MAC  service method-output-action:	GetLineServerList Response
int __MAC__GetLineServerList(
    MAC__GetLineServerList*             MAC__GetLineServerList_,	///< Input parameter
    MAC__GetLineServerListResponse     &MAC__GetLineServerListResponse_	///< Output parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   __MAC__GetServerInfo                                                     *
 *                                                                            *
\******************************************************************************/


/** Operation "__MAC__GetServerInfo" of service binding "MachineWSServiceImplServiceSoapBinding".

  - SOAP document/literal style messaging

  - Default endpoints:
    - http://218.26.30.70:9090/WorkHelper/ws/machineWSService

  - Addressing input action: ""

  - Addressing output action: "Response"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call___MAC__GetServerInfo(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    MAC__GetServerInfo*                 MAC__GetServerInfo_,
    // output parameters:
    MAC__GetServerInfoResponse         &MAC__GetServerInfoResponse_
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int __MAC__GetServerInfo(
    struct soap *soap,
    // input parameters:
    MAC__GetServerInfo*                 MAC__GetServerInfo_,
    // output parameters:
    MAC__GetServerInfoResponse         &MAC__GetServerInfoResponse_
  );
@endcode

C++ proxy class (defined in soapMachineWSServiceImplServiceSoapBindingProxy.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapMachineWSServiceImplServiceSoapBindingService.h generated with soapcpp2):
@code
  class MachineWSServiceImplServiceSoapBindingService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap MAC  service method-protocol:	GetServerInfo SOAP
//gsoap MAC  service method-style:	GetServerInfo document
//gsoap MAC  service method-encoding:	GetServerInfo literal
//gsoap MAC  service method-action:	GetServerInfo ""
//gsoap MAC  service method-output-action:	GetServerInfo Response
int __MAC__GetServerInfo(
    MAC__GetServerInfo*                 MAC__GetServerInfo_,	///< Input parameter
    MAC__GetServerInfoResponse         &MAC__GetServerInfoResponse_	///< Output parameter
);

/** @page MachineWSServiceImplServiceSoapBinding Binding "MachineWSServiceImplServiceSoapBinding"

@section MachineWSServiceImplServiceSoapBinding_policy_enablers Policy Enablers of Binding "MachineWSServiceImplServiceSoapBinding"

None specified.

*/

/******************************************************************************\
 *                                                                            *
 * XML Data Binding                                                           *
 *                                                                            *
\******************************************************************************/


/** @page page_XMLDataBinding XML Data Binding

SOAP/XML services use data bindings that are contractually bound by WSDLs and
are auto-generated by wsdl2h and soapcpp2 (see Service Bindings). Plain data
bindings are adopted from XML schemas as part of the WSDL types section or when
running wsdl2h on a set of schemas to produce non-SOAP-based XML data bindings.

@note The following readers and writers are C/C++ data type (de)serializers
auto-generated by wsdl2h and soapcpp2. Run soapcpp2 on this file to generate the
(de)serialization code, which is stored in soapC.c[pp]. Include "soapH.h" in
your code to import these data type and function declarations. Only use the
soapcpp2-generated files in your project build. Do not include the wsdl2h-
generated .h file in your code.

@note Data can be read and deserialized from:
  - an int file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = (int)...
  - a C++ stream (istream, stringstream), using soap->is = (istream*)...
  - a C string, using soap->is = (const char*)...
  - any input, using the soap->frecv() callback

@note Data can be serialized and written to:
  - an int file descriptor, using soap->sendfd = (int)...
  - a socket, using soap->socket = (int)...
  - a C++ stream (ostream, stringstream), using soap->os = (ostream*)...
  - a C string, using soap->os = (const char**)...
  - any output, using the soap->fsend() callback

@note The following options are available for (de)serialization control:
  - soap->encodingStyle = NULL; to remove SOAP 1.1/1.2 encodingStyle
  - soap_set_mode(soap, SOAP_XML_TREE); XML without id-ref (no cycles!)
  - soap_set_mode(soap, SOAP_XML_GRAPH); XML with id-ref (including cycles)
  - soap_set_namespaces(soap, struct Namespace *nsmap); to set xmlns bindings


*/

/**

@section MAC Top-level root elements of schema "http://machine.webService.workHelper.cnki.com/"

  - <MAC:fetchRobotConfig> (use wsdl2h option -g to auto-generate type _MAC__fetchRobotConfig)

  - <MAC:fetchRobotConfigResponse> (use wsdl2h option -g to auto-generate type _MAC__fetchRobotConfigResponse)

  - <MAC:GetLineServerInfo> (use wsdl2h option -g to auto-generate type _MAC__GetLineServerInfo)

  - <MAC:GetLineServerInfoResponse> (use wsdl2h option -g to auto-generate type _MAC__GetLineServerInfoResponse)

  - <MAC:addRobotRunState> (use wsdl2h option -g to auto-generate type _MAC__addRobotRunState)

  - <MAC:addRobotRunStateResponse> (use wsdl2h option -g to auto-generate type _MAC__addRobotRunStateResponse)

  - <MAC:GetLineServerList> (use wsdl2h option -g to auto-generate type _MAC__GetLineServerList)

  - <MAC:GetLineServerListResponse> (use wsdl2h option -g to auto-generate type _MAC__GetLineServerListResponse)

  - <MAC:GetServerInfo> (use wsdl2h option -g to auto-generate type _MAC__GetServerInfo)

  - <MAC:GetServerInfoResponse> (use wsdl2h option -g to auto-generate type _MAC__GetServerInfoResponse)

*/

#define SOAP_NAMESPACE_OF_SER	"http://Fantasy/WebServiceDemo/"
//gsoap SER   schema namespace:	http://Fantasy/WebServiceDemo/
//gsoap SER   schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Forward Declarations                                                       *
 *                                                                            *
\******************************************************************************/



/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   http://Fantasy/WebServiceDemo/                                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   http://Fantasy/WebServiceDemo/                                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   http://Fantasy/WebServiceDemo/                                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   http://Fantasy/WebServiceDemo/                                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/

// This service supports SOAP 1.2 namespaces:
#import "soap12.h"

//gsoap SER  service name:	Service1Soap 
//gsoap SER  service type:	Service1Soap 
//gsoap SER  service port:	http://218.26.30.70:81/WebServiceDemo/Service1.asmx 
//gsoap SER  service namespace:	http://Fantasy/WebServiceDemo/ 
//gsoap SER  service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage Service Definitions

@section Service_bindings Service Bindings

  - @ref Service1Soap

@section Service_more More Information

  - @ref page_notes "Notes"

  - @ref page_XMLDataBinding "XML Data Binding"

  - @ref SOAP_ENV__Header "SOAP Header Content" (when applicable)

  - @ref SOAP_ENV__Detail "SOAP Fault Detail Content" (when applicable)


*/

/** @page Service1Soap Binding "Service1Soap"

@section Service1Soap_operations Operations of Binding "Service1Soap"

  - @ref SER__AddNumbers

  - @ref SER__clearLink

  - @ref SER__showExistLink

  - @ref SER__TestLinkSqlserver

  - @ref SER__executeSql

  - @ref SER__executeSql_USCOREbackEncord

  - @ref SER__executeSql_USCOREencode

  - @ref SER__insertXml

  - @ref SER__executeStorageProcess

  - @ref SER__AddFileToSql

  - @ref SER__AddNumbers_

  - @ref SER__clearLink_

  - @ref SER__showExistLink_

  - @ref SER__TestLinkSqlserver_

  - @ref SER__executeSql_

  - @ref SER__executeSql_USCOREbackEncord_

  - @ref SER__executeSql_USCOREencode_

  - @ref SER__insertXml_

  - @ref SER__executeStorageProcess_

  - @ref SER__AddFileToSql_

@section Service1Soap_ports Default endpoints of Binding "Service1Soap"

  - http://218.26.30.70:81/WebServiceDemo/Service1.asmx


*/

/******************************************************************************\
 *                                                                            *
 * Service Binding                                                            *
 *   Service1Soap                                                             *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__AddNumbers                                                          *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__AddNumbers" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/AddNumbers"

  - Addressing input action: "http://Fantasy/WebServiceDemo/AddNumbers"

  - Addressing output action: "http://Fantasy/WebServiceDemo/AddNumbersResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__AddNumbers(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    int                                 NumberOne,
    int                                 NumberTwo,
    // output parameters:
    int                                &AddNumbersResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__AddNumbers(
    struct soap *soap,
    // input parameters:
    int                                 NumberOne,
    int                                 NumberTwo,
    // output parameters:
    int                                &AddNumbersResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	AddNumbers SOAP
//gsoap SER  service method-style:	AddNumbers rpc
//gsoap SER  service method-encoding:	AddNumbers http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	AddNumbers http://Fantasy/WebServiceDemo/AddNumbers
//gsoap SER  service method-output-action:	AddNumbers http://Fantasy/WebServiceDemo/AddNumbersResponse
int SER__AddNumbers(
    int                                 :NumberOne,	///< Input parameter, :unqualified name as per RPC encoding
    int                                 :NumberTwo,	///< Input parameter, :unqualified name as per RPC encoding
    int                                &:AddNumbersResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__clearLink                                                           *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__clearLink" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/clearLink"

  - Addressing input action: "http://Fantasy/WebServiceDemo/clearLink"

  - Addressing output action: "http://Fantasy/WebServiceDemo/clearLinkResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__clearLink(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    bool                                bTimeContrl,
    // output parameters:
    std::wstring                       &clearLinkResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__clearLink(
    struct soap *soap,
    // input parameters:
    bool                                bTimeContrl,
    // output parameters:
    std::wstring                       &clearLinkResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	clearLink SOAP
//gsoap SER  service method-style:	clearLink rpc
//gsoap SER  service method-encoding:	clearLink http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	clearLink http://Fantasy/WebServiceDemo/clearLink
//gsoap SER  service method-output-action:	clearLink http://Fantasy/WebServiceDemo/clearLinkResponse
int SER__clearLink(
    bool                                :bTimeContrl,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:clearLinkResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__showExistLink                                                       *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__showExistLink" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/showExistLink"

  - Addressing input action: "http://Fantasy/WebServiceDemo/showExistLink"

  - Addressing output action: "http://Fantasy/WebServiceDemo/showExistLinkResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__showExistLink(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    // output parameters:
    std::wstring                       &showExistLinkResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__showExistLink(
    struct soap *soap,
    // input parameters:
    // output parameters:
    std::wstring                       &showExistLinkResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	showExistLink SOAP
//gsoap SER  service method-style:	showExistLink rpc
//gsoap SER  service method-encoding:	showExistLink http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	showExistLink http://Fantasy/WebServiceDemo/showExistLink
//gsoap SER  service method-output-action:	showExistLink http://Fantasy/WebServiceDemo/showExistLinkResponse
int SER__showExistLink(
    std::wstring                       &:showExistLinkResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__TestLinkSqlserver                                                   *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__TestLinkSqlserver" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/TestLinkSqlserver"

  - Addressing input action: "http://Fantasy/WebServiceDemo/TestLinkSqlserver"

  - Addressing output action: "http://Fantasy/WebServiceDemo/TestLinkSqlserverResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__TestLinkSqlserver(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    // output parameters:
    std::wstring                       &TestLinkSqlserverResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__TestLinkSqlserver(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    // output parameters:
    std::wstring                       &TestLinkSqlserverResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	TestLinkSqlserver SOAP
//gsoap SER  service method-style:	TestLinkSqlserver rpc
//gsoap SER  service method-encoding:	TestLinkSqlserver http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	TestLinkSqlserver http://Fantasy/WebServiceDemo/TestLinkSqlserver
//gsoap SER  service method-output-action:	TestLinkSqlserver http://Fantasy/WebServiceDemo/TestLinkSqlserverResponse
int SER__TestLinkSqlserver(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:TestLinkSqlserverResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeSql                                                          *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeSql" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeSql"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeSql"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeSqlResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeSql(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSqlResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeSql(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSqlResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeSql SOAP
//gsoap SER  service method-style:	executeSql rpc
//gsoap SER  service method-encoding:	executeSql http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	executeSql http://Fantasy/WebServiceDemo/executeSql
//gsoap SER  service method-output-action:	executeSql http://Fantasy/WebServiceDemo/executeSqlResponse
int SER__executeSql(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sSql,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeSqlResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeSql_USCOREbackEncord                                         *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeSql_USCOREbackEncord" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeSql_backEncord"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeSql_backEncord"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeSql_backEncordResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeSql_USCOREbackEncord(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREbackEncordResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeSql_USCOREbackEncord(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREbackEncordResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeSql_USCOREbackEncord SOAP
//gsoap SER  service method-style:	executeSql_USCOREbackEncord rpc
//gsoap SER  service method-encoding:	executeSql_USCOREbackEncord http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	executeSql_USCOREbackEncord http://Fantasy/WebServiceDemo/executeSql_backEncord
//gsoap SER  service method-output-action:	executeSql_USCOREbackEncord http://Fantasy/WebServiceDemo/executeSql_backEncordResponse
int SER__executeSql_USCOREbackEncord(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sSql,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeSql_USCOREbackEncordResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeSql_USCOREencode                                             *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeSql_USCOREencode" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeSql_encode"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeSql_encode"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeSql_encodeResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeSql_USCOREencode(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREencodeResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeSql_USCOREencode(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREencodeResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeSql_USCOREencode SOAP
//gsoap SER  service method-style:	executeSql_USCOREencode rpc
//gsoap SER  service method-encoding:	executeSql_USCOREencode http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	executeSql_USCOREencode http://Fantasy/WebServiceDemo/executeSql_encode
//gsoap SER  service method-output-action:	executeSql_USCOREencode http://Fantasy/WebServiceDemo/executeSql_encodeResponse
int SER__executeSql_USCOREencode(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sSql,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeSql_USCOREencodeResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__insertXml                                                           *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__insertXml" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/insertXml"

  - Addressing input action: "http://Fantasy/WebServiceDemo/insertXml"

  - Addressing output action: "http://Fantasy/WebServiceDemo/insertXmlResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__insertXml(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strXml,
    bool                                encode,
    // output parameters:
    std::wstring                       &insertXmlResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__insertXml(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strXml,
    bool                                encode,
    // output parameters:
    std::wstring                       &insertXmlResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	insertXml SOAP
//gsoap SER  service method-style:	insertXml rpc
//gsoap SER  service method-encoding:	insertXml http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	insertXml http://Fantasy/WebServiceDemo/insertXml
//gsoap SER  service method-output-action:	insertXml http://Fantasy/WebServiceDemo/insertXmlResponse
int SER__insertXml(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :strXml,	///< Input parameter, :unqualified name as per RPC encoding
    bool                                :encode,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:insertXmlResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeStorageProcess                                               *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeStorageProcess" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeStorageProcess"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeStorageProcess"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeStorageProcessResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeStorageProcess(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        StorageProcessName,
    std::wstring                        Parameters,
    // output parameters:
    std::wstring                       &executeStorageProcessResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeStorageProcess(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        StorageProcessName,
    std::wstring                        Parameters,
    // output parameters:
    std::wstring                       &executeStorageProcessResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeStorageProcess SOAP
//gsoap SER  service method-style:	executeStorageProcess rpc
//gsoap SER  service method-encoding:	executeStorageProcess http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	executeStorageProcess http://Fantasy/WebServiceDemo/executeStorageProcess
//gsoap SER  service method-output-action:	executeStorageProcess http://Fantasy/WebServiceDemo/executeStorageProcessResponse
int SER__executeStorageProcess(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :StorageProcessName,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :Parameters,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeStorageProcessResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__AddFileToSql                                                        *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__AddFileToSql" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/AddFileToSql"

  - Addressing input action: "http://Fantasy/WebServiceDemo/AddFileToSql"

  - Addressing output action: "http://Fantasy/WebServiceDemo/AddFileToSqlResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__AddFileToSql(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strFileName,
    std::wstring                        sPointer,
    std::wstring                        tablenamefieldname,
    std::wstring                        fileIP,
    std::wstring                        fileUse,
    std::wstring                        filePassword,
    // output parameters:
    std::wstring                       &AddFileToSqlResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__AddFileToSql(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strFileName,
    std::wstring                        sPointer,
    std::wstring                        tablenamefieldname,
    std::wstring                        fileIP,
    std::wstring                        fileUse,
    std::wstring                        filePassword,
    // output parameters:
    std::wstring                       &AddFileToSqlResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	AddFileToSql SOAP
//gsoap SER  service method-style:	AddFileToSql rpc
//gsoap SER  service method-encoding:	AddFileToSql http://schemas.xmlsoap.org/soap/encoding/
//gsoap SER  service method-input-action:	AddFileToSql http://Fantasy/WebServiceDemo/AddFileToSql
//gsoap SER  service method-output-action:	AddFileToSql http://Fantasy/WebServiceDemo/AddFileToSqlResponse
int SER__AddFileToSql(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :strFileName,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sPointer,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :tablenamefieldname,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :fileIP,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :fileUse,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :filePassword,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:AddFileToSqlResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__AddNumbers_                                                         *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__AddNumbers_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/AddNumbers"

  - Addressing input action: "http://Fantasy/WebServiceDemo/AddNumbers"

  - Addressing output action: "http://Fantasy/WebServiceDemo/AddNumbersResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__AddNumbers_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    int                                 NumberOne,
    int                                 NumberTwo,
    // output parameters:
    int                                &AddNumbersResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__AddNumbers_(
    struct soap *soap,
    // input parameters:
    int                                 NumberOne,
    int                                 NumberTwo,
    // output parameters:
    int                                &AddNumbersResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	AddNumbers_ SOAP
//gsoap SER  service method-style:	AddNumbers_ rpc
//gsoap SER  service method-encoding:	AddNumbers_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	AddNumbers_ http://Fantasy/WebServiceDemo/AddNumbers
//gsoap SER  service method-output-action:	AddNumbers_ http://Fantasy/WebServiceDemo/AddNumbersResponse
int SER__AddNumbers_(
    int                                 :NumberOne,	///< Input parameter, :unqualified name as per RPC encoding
    int                                 :NumberTwo,	///< Input parameter, :unqualified name as per RPC encoding
    int                                &:AddNumbersResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__clearLink_                                                          *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__clearLink_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/clearLink"

  - Addressing input action: "http://Fantasy/WebServiceDemo/clearLink"

  - Addressing output action: "http://Fantasy/WebServiceDemo/clearLinkResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__clearLink_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    bool                                bTimeContrl,
    // output parameters:
    std::wstring                       &clearLinkResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__clearLink_(
    struct soap *soap,
    // input parameters:
    bool                                bTimeContrl,
    // output parameters:
    std::wstring                       &clearLinkResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	clearLink_ SOAP
//gsoap SER  service method-style:	clearLink_ rpc
//gsoap SER  service method-encoding:	clearLink_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	clearLink_ http://Fantasy/WebServiceDemo/clearLink
//gsoap SER  service method-output-action:	clearLink_ http://Fantasy/WebServiceDemo/clearLinkResponse
int SER__clearLink_(
    bool                                :bTimeContrl,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:clearLinkResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__showExistLink_                                                      *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__showExistLink_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/showExistLink"

  - Addressing input action: "http://Fantasy/WebServiceDemo/showExistLink"

  - Addressing output action: "http://Fantasy/WebServiceDemo/showExistLinkResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__showExistLink_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    // output parameters:
    std::wstring                       &showExistLinkResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__showExistLink_(
    struct soap *soap,
    // input parameters:
    // output parameters:
    std::wstring                       &showExistLinkResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	showExistLink_ SOAP
//gsoap SER  service method-style:	showExistLink_ rpc
//gsoap SER  service method-encoding:	showExistLink_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	showExistLink_ http://Fantasy/WebServiceDemo/showExistLink
//gsoap SER  service method-output-action:	showExistLink_ http://Fantasy/WebServiceDemo/showExistLinkResponse
int SER__showExistLink_(
    std::wstring                       &:showExistLinkResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__TestLinkSqlserver_                                                  *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__TestLinkSqlserver_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/TestLinkSqlserver"

  - Addressing input action: "http://Fantasy/WebServiceDemo/TestLinkSqlserver"

  - Addressing output action: "http://Fantasy/WebServiceDemo/TestLinkSqlserverResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__TestLinkSqlserver_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    // output parameters:
    std::wstring                       &TestLinkSqlserverResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__TestLinkSqlserver_(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    // output parameters:
    std::wstring                       &TestLinkSqlserverResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	TestLinkSqlserver_ SOAP
//gsoap SER  service method-style:	TestLinkSqlserver_ rpc
//gsoap SER  service method-encoding:	TestLinkSqlserver_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	TestLinkSqlserver_ http://Fantasy/WebServiceDemo/TestLinkSqlserver
//gsoap SER  service method-output-action:	TestLinkSqlserver_ http://Fantasy/WebServiceDemo/TestLinkSqlserverResponse
int SER__TestLinkSqlserver_(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:TestLinkSqlserverResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeSql_                                                         *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeSql_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeSql"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeSql"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeSqlResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeSql_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSqlResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeSql_(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSqlResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeSql_ SOAP
//gsoap SER  service method-style:	executeSql_ rpc
//gsoap SER  service method-encoding:	executeSql_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	executeSql_ http://Fantasy/WebServiceDemo/executeSql
//gsoap SER  service method-output-action:	executeSql_ http://Fantasy/WebServiceDemo/executeSqlResponse
int SER__executeSql_(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sSql,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeSqlResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeSql_USCOREbackEncord_                                        *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeSql_USCOREbackEncord_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeSql_backEncord"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeSql_backEncord"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeSql_backEncordResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeSql_USCOREbackEncord_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREbackEncordResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeSql_USCOREbackEncord_(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREbackEncordResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeSql_USCOREbackEncord_ SOAP
//gsoap SER  service method-style:	executeSql_USCOREbackEncord_ rpc
//gsoap SER  service method-encoding:	executeSql_USCOREbackEncord_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	executeSql_USCOREbackEncord_ http://Fantasy/WebServiceDemo/executeSql_backEncord
//gsoap SER  service method-output-action:	executeSql_USCOREbackEncord_ http://Fantasy/WebServiceDemo/executeSql_backEncordResponse
int SER__executeSql_USCOREbackEncord_(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sSql,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeSql_USCOREbackEncordResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeSql_USCOREencode_                                            *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeSql_USCOREencode_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeSql_encode"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeSql_encode"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeSql_encodeResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeSql_USCOREencode_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREencodeResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeSql_USCOREencode_(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        sSql,
    // output parameters:
    std::wstring                       &executeSql_USCOREencodeResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeSql_USCOREencode_ SOAP
//gsoap SER  service method-style:	executeSql_USCOREencode_ rpc
//gsoap SER  service method-encoding:	executeSql_USCOREencode_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	executeSql_USCOREencode_ http://Fantasy/WebServiceDemo/executeSql_encode
//gsoap SER  service method-output-action:	executeSql_USCOREencode_ http://Fantasy/WebServiceDemo/executeSql_encodeResponse
int SER__executeSql_USCOREencode_(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sSql,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeSql_USCOREencodeResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__insertXml_                                                          *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__insertXml_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/insertXml"

  - Addressing input action: "http://Fantasy/WebServiceDemo/insertXml"

  - Addressing output action: "http://Fantasy/WebServiceDemo/insertXmlResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__insertXml_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strXml,
    bool                                encode,
    // output parameters:
    std::wstring                       &insertXmlResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__insertXml_(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strXml,
    bool                                encode,
    // output parameters:
    std::wstring                       &insertXmlResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	insertXml_ SOAP
//gsoap SER  service method-style:	insertXml_ rpc
//gsoap SER  service method-encoding:	insertXml_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	insertXml_ http://Fantasy/WebServiceDemo/insertXml
//gsoap SER  service method-output-action:	insertXml_ http://Fantasy/WebServiceDemo/insertXmlResponse
int SER__insertXml_(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :strXml,	///< Input parameter, :unqualified name as per RPC encoding
    bool                                :encode,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:insertXmlResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__executeStorageProcess_                                              *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__executeStorageProcess_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/executeStorageProcess"

  - Addressing input action: "http://Fantasy/WebServiceDemo/executeStorageProcess"

  - Addressing output action: "http://Fantasy/WebServiceDemo/executeStorageProcessResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__executeStorageProcess_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        StorageProcessName,
    std::wstring                        Parameters,
    // output parameters:
    std::wstring                       &executeStorageProcessResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__executeStorageProcess_(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        StorageProcessName,
    std::wstring                        Parameters,
    // output parameters:
    std::wstring                       &executeStorageProcessResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	executeStorageProcess_ SOAP
//gsoap SER  service method-style:	executeStorageProcess_ rpc
//gsoap SER  service method-encoding:	executeStorageProcess_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	executeStorageProcess_ http://Fantasy/WebServiceDemo/executeStorageProcess
//gsoap SER  service method-output-action:	executeStorageProcess_ http://Fantasy/WebServiceDemo/executeStorageProcessResponse
int SER__executeStorageProcess_(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :StorageProcessName,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :Parameters,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:executeStorageProcessResult	///< Output parameter, :unqualified name as per RPC encoding
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   SER__AddFileToSql_                                                       *
 *                                                                            *
\******************************************************************************/


/** Operation "SER__AddFileToSql_" of service binding "Service1Soap".

  - SOAP RPC encodingStyle="http://www.w3.org/2003/05/soap-encoding"

  - Default endpoints:
    - http://218.26.30.70:81/WebServiceDemo/Service1.asmx

  - Default SOAP action or REST location path:
    - "http://Fantasy/WebServiceDemo/AddFileToSql"

  - Addressing input action: "http://Fantasy/WebServiceDemo/AddFileToSql"

  - Addressing output action: "http://Fantasy/WebServiceDemo/AddFileToSqlResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_SER__AddFileToSql_(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strFileName,
    std::wstring                        sPointer,
    std::wstring                        tablenamefieldname,
    std::wstring                        fileIP,
    std::wstring                        fileUse,
    std::wstring                        filePassword,
    // output parameters:
    std::wstring                       &AddFileToSqlResult
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int SER__AddFileToSql_(
    struct soap *soap,
    // input parameters:
    std::wstring                        serverInfo,
    std::wstring                        strFileName,
    std::wstring                        sPointer,
    std::wstring                        tablenamefieldname,
    std::wstring                        fileIP,
    std::wstring                        fileUse,
    std::wstring                        filePassword,
    // output parameters:
    std::wstring                       &AddFileToSqlResult
  );
@endcode

C++ proxy class (defined in soapService1SoapProxy.h generated with soapcpp2):
@code
  class Service1SoapProxy;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use proxy classes;

C++ service class (defined in soapService1SoapService.h generated with soapcpp2):
@code
  class Service1SoapService;
@endcode
Important: use soapcpp2 option '-j' (or '-i') to generate improved and easy-to-use service classes;

*/

//gsoap SER  service method-protocol:	AddFileToSql_ SOAP
//gsoap SER  service method-style:	AddFileToSql_ rpc
//gsoap SER  service method-encoding:	AddFileToSql_ http://www.w3.org/2003/05/soap-encoding
//gsoap SER  service method-input-action:	AddFileToSql_ http://Fantasy/WebServiceDemo/AddFileToSql
//gsoap SER  service method-output-action:	AddFileToSql_ http://Fantasy/WebServiceDemo/AddFileToSqlResponse
int SER__AddFileToSql_(
    std::wstring                        :serverInfo,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :strFileName,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :sPointer,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :tablenamefieldname,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :fileIP,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :fileUse,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                        :filePassword,	///< Input parameter, :unqualified name as per RPC encoding
    std::wstring                       &:AddFileToSqlResult	///< Output parameter, :unqualified name as per RPC encoding
);

/** @page Service1Soap Binding "Service1Soap"

@section Service1Soap_policy_enablers Policy Enablers of Binding "Service1Soap"

None specified.

*/

/******************************************************************************\
 *                                                                            *
 * XML Data Binding                                                           *
 *                                                                            *
\******************************************************************************/


/** @page page_XMLDataBinding XML Data Binding

SOAP/XML services use data bindings that are contractually bound by WSDLs and
are auto-generated by wsdl2h and soapcpp2 (see Service Bindings). Plain data
bindings are adopted from XML schemas as part of the WSDL types section or when
running wsdl2h on a set of schemas to produce non-SOAP-based XML data bindings.

@note The following readers and writers are C/C++ data type (de)serializers
auto-generated by wsdl2h and soapcpp2. Run soapcpp2 on this file to generate the
(de)serialization code, which is stored in soapC.c[pp]. Include "soapH.h" in
your code to import these data type and function declarations. Only use the
soapcpp2-generated files in your project build. Do not include the wsdl2h-
generated .h file in your code.

@note Data can be read and deserialized from:
  - an int file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = (int)...
  - a C++ stream (istream, stringstream), using soap->is = (istream*)...
  - a C string, using soap->is = (const char*)...
  - any input, using the soap->frecv() callback

@note Data can be serialized and written to:
  - an int file descriptor, using soap->sendfd = (int)...
  - a socket, using soap->socket = (int)...
  - a C++ stream (ostream, stringstream), using soap->os = (ostream*)...
  - a C string, using soap->os = (const char**)...
  - any output, using the soap->fsend() callback

@note The following options are available for (de)serialization control:
  - soap->encodingStyle = NULL; to remove SOAP 1.1/1.2 encodingStyle
  - soap_set_mode(soap, SOAP_XML_TREE); XML without id-ref (no cycles!)
  - soap_set_mode(soap, SOAP_XML_GRAPH); XML with id-ref (including cycles)
  - soap_set_namespaces(soap, struct Namespace *nsmap); to set xmlns bindings


*/

/**

@section SER Top-level root elements of schema "http://Fantasy/WebServiceDemo/"

*/

