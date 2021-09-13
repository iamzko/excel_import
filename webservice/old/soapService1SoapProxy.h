/* soapService1SoapProxy.h
   Generated by gSOAP 2.8.111 for .\Service1.asmx.h

gSOAP XML Web services tools
Copyright (C) 2000-2021, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef soapService1SoapProxy_H
#define soapService1SoapProxy_H
#include "soapH.h"

    class SOAP_CMAC Service1SoapProxy : public soap {
      public:
        /// Endpoint URL of service 'Service1SoapProxy' (change as needed)
        const char *soap_endpoint;
        /// Variables globally declared in .\Service1.asmx.h, if any
        /// Construct a proxy with new managing context
        Service1SoapProxy();
        /// Copy constructor
        Service1SoapProxy(const Service1SoapProxy& rhs);
        /// Construct proxy given a managing context
        Service1SoapProxy(const struct soap&);
        /// Construct proxy given a managing context and endpoint URL
        Service1SoapProxy(const struct soap&, const char *soap_endpoint_url);
        /// Constructor taking an endpoint URL
        Service1SoapProxy(const char *soap_endpoint_url);
        /// Constructor taking input and output mode flags for the new managing context
        Service1SoapProxy(soap_mode iomode);
        /// Constructor taking endpoint URL and input and output mode flags for the new managing context
        Service1SoapProxy(const char *soap_endpoint_url, soap_mode iomode);
        /// Constructor taking input and output mode flags for the new managing context
        Service1SoapProxy(soap_mode imode, soap_mode omode);
        /// Destructor deletes deserialized data and its managing context
        virtual ~Service1SoapProxy();
        /// Initializer used by constructors
        virtual void Service1SoapProxy_init(soap_mode imode, soap_mode omode);
        /// Return a copy that has a new managing context with the same engine state
        virtual Service1SoapProxy *copy();
        /// Copy assignment
        Service1SoapProxy& operator=(const Service1SoapProxy&);
        /// Delete all deserialized data (uses soap_destroy() and soap_end())
        virtual void destroy();
        /// Delete all deserialized data and reset to default
        virtual void reset();
        /// Disables and removes SOAP Header from message by setting soap->header = NULL
        virtual void soap_noheader();
        /// Get SOAP Header structure (i.e. soap->header, which is NULL when absent)
        virtual ::SOAP_ENV__Header *soap_header();
        /// Get SOAP Fault structure (i.e. soap->fault, which is NULL when absent)
        virtual ::SOAP_ENV__Fault *soap_fault();
        /// Get SOAP Fault subcode QName string (NULL when absent)
        virtual const char *soap_fault_subcode();
        /// Get SOAP Fault string/reason (NULL when absent)
        virtual const char *soap_fault_string();
        /// Get SOAP Fault detail XML string (NULL when absent)
        virtual const char *soap_fault_detail();
        /// Close connection (normally automatic, except for send_X ops)
        virtual int soap_close_socket();
        /// Force close connection (can kill a thread blocked on IO)
        virtual int soap_force_close_socket();
        /// Print fault
        virtual void soap_print_fault(FILE*);
    #ifndef WITH_LEAN
    #ifndef WITH_COMPAT
        /// Print fault to stream
        virtual void soap_stream_fault(std::ostream&);
    #endif
        /// Write fault to buffer
        virtual char *soap_sprint_fault(char *buf, size_t len);
    #endif
        //
        /// Web service synchronous operation 'AddNumbers' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int AddNumbers(int NumberOne, int NumberTwo, int &AddNumbersResult) { return this->AddNumbers(NULL, NULL, NumberOne, NumberTwo, AddNumbersResult); }
        /// Web service synchronous operation 'AddNumbers' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int AddNumbers(const char *soap_endpoint_url, const char *soap_action, int NumberOne, int NumberTwo, int &AddNumbersResult) { return this->send_AddNumbers(soap_endpoint_url, soap_action, NumberOne, NumberTwo) || this->recv_AddNumbers(AddNumbersResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_AddNumbers' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_AddNumbers(const char *soap_endpoint_url, const char *soap_action, int NumberOne, int NumberTwo);
        /// Web service asynchronous operation 'recv_AddNumbers' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_AddNumbers(int &AddNumbersResult);
        //
        /// Web service synchronous operation 'clearLink' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int clearLink(bool bTimeContrl, std::wstring &clearLinkResult) { return this->clearLink(NULL, NULL, bTimeContrl, clearLinkResult); }
        /// Web service synchronous operation 'clearLink' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int clearLink(const char *soap_endpoint_url, const char *soap_action, bool bTimeContrl, std::wstring &clearLinkResult) { return this->send_clearLink(soap_endpoint_url, soap_action, bTimeContrl) || this->recv_clearLink(clearLinkResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_clearLink' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_clearLink(const char *soap_endpoint_url, const char *soap_action, bool bTimeContrl);
        /// Web service asynchronous operation 'recv_clearLink' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_clearLink(std::wstring &clearLinkResult);
        //
        /// Web service synchronous operation 'showExistLink' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int showExistLink(std::wstring &showExistLinkResult) { return this->showExistLink(NULL, NULL, showExistLinkResult); }
        /// Web service synchronous operation 'showExistLink' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int showExistLink(const char *soap_endpoint_url, const char *soap_action, std::wstring &showExistLinkResult) { return this->send_showExistLink(soap_endpoint_url, soap_action) || this->recv_showExistLink(showExistLinkResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_showExistLink' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_showExistLink(const char *soap_endpoint_url, const char *soap_action);
        /// Web service asynchronous operation 'recv_showExistLink' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_showExistLink(std::wstring &showExistLinkResult);
        //
        /// Web service synchronous operation 'TestLinkSqlserver' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int TestLinkSqlserver(const std::wstring& serverInfo, std::wstring &TestLinkSqlserverResult) { return this->TestLinkSqlserver(NULL, NULL, serverInfo, TestLinkSqlserverResult); }
        /// Web service synchronous operation 'TestLinkSqlserver' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int TestLinkSqlserver(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, std::wstring &TestLinkSqlserverResult) { return this->send_TestLinkSqlserver(soap_endpoint_url, soap_action, serverInfo) || this->recv_TestLinkSqlserver(TestLinkSqlserverResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_TestLinkSqlserver' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_TestLinkSqlserver(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo);
        /// Web service asynchronous operation 'recv_TestLinkSqlserver' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_TestLinkSqlserver(std::wstring &TestLinkSqlserverResult);
        //
        /// Web service synchronous operation 'executeSql' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql(const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSqlResult) { return this->executeSql(NULL, NULL, serverInfo, sSql, executeSqlResult); }
        /// Web service synchronous operation 'executeSql' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSqlResult) { return this->send_executeSql(soap_endpoint_url, soap_action, serverInfo, sSql) || this->recv_executeSql(executeSqlResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeSql' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeSql(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql);
        /// Web service asynchronous operation 'recv_executeSql' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeSql(std::wstring &executeSqlResult);
        //
        /// Web service synchronous operation 'executeSql_backEncord' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREbackEncord(const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREbackEncordResult) { return this->executeSql_USCOREbackEncord(NULL, NULL, serverInfo, sSql, executeSql_USCOREbackEncordResult); }
        /// Web service synchronous operation 'executeSql_backEncord' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREbackEncord(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREbackEncordResult) { return this->send_executeSql_USCOREbackEncord(soap_endpoint_url, soap_action, serverInfo, sSql) || this->recv_executeSql_USCOREbackEncord(executeSql_USCOREbackEncordResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeSql_backEncord' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeSql_USCOREbackEncord(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql);
        /// Web service asynchronous operation 'recv_executeSql_backEncord' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeSql_USCOREbackEncord(std::wstring &executeSql_USCOREbackEncordResult);
        //
        /// Web service synchronous operation 'executeSql_encode' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREencode(const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREencodeResult) { return this->executeSql_USCOREencode(NULL, NULL, serverInfo, sSql, executeSql_USCOREencodeResult); }
        /// Web service synchronous operation 'executeSql_encode' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREencode(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREencodeResult) { return this->send_executeSql_USCOREencode(soap_endpoint_url, soap_action, serverInfo, sSql) || this->recv_executeSql_USCOREencode(executeSql_USCOREencodeResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeSql_encode' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeSql_USCOREencode(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql);
        /// Web service asynchronous operation 'recv_executeSql_encode' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeSql_USCOREencode(std::wstring &executeSql_USCOREencodeResult);
        //
        /// Web service synchronous operation 'insertXml' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int insertXml(const std::wstring& serverInfo, const std::wstring& strXml, bool encode, std::wstring &insertXmlResult) { return this->insertXml(NULL, NULL, serverInfo, strXml, encode, insertXmlResult); }
        /// Web service synchronous operation 'insertXml' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int insertXml(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strXml, bool encode, std::wstring &insertXmlResult) { return this->send_insertXml(soap_endpoint_url, soap_action, serverInfo, strXml, encode) || this->recv_insertXml(insertXmlResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_insertXml' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_insertXml(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strXml, bool encode);
        /// Web service asynchronous operation 'recv_insertXml' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_insertXml(std::wstring &insertXmlResult);
        //
        /// Web service synchronous operation 'executeStorageProcess' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeStorageProcess(const std::wstring& serverInfo, const std::wstring& StorageProcessName, const std::wstring& Parameters, std::wstring &executeStorageProcessResult) { return this->executeStorageProcess(NULL, NULL, serverInfo, StorageProcessName, Parameters, executeStorageProcessResult); }
        /// Web service synchronous operation 'executeStorageProcess' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeStorageProcess(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& StorageProcessName, const std::wstring& Parameters, std::wstring &executeStorageProcessResult) { return this->send_executeStorageProcess(soap_endpoint_url, soap_action, serverInfo, StorageProcessName, Parameters) || this->recv_executeStorageProcess(executeStorageProcessResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeStorageProcess' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeStorageProcess(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& StorageProcessName, const std::wstring& Parameters);
        /// Web service asynchronous operation 'recv_executeStorageProcess' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeStorageProcess(std::wstring &executeStorageProcessResult);
        //
        /// Web service synchronous operation 'AddFileToSql' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int AddFileToSql(const std::wstring& serverInfo, const std::wstring& strFileName, const std::wstring& sPointer, const std::wstring& tablenamefieldname, const std::wstring& fileIP, const std::wstring& fileUse, const std::wstring& filePassword, std::wstring &AddFileToSqlResult) { return this->AddFileToSql(NULL, NULL, serverInfo, strFileName, sPointer, tablenamefieldname, fileIP, fileUse, filePassword, AddFileToSqlResult); }
        /// Web service synchronous operation 'AddFileToSql' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int AddFileToSql(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strFileName, const std::wstring& sPointer, const std::wstring& tablenamefieldname, const std::wstring& fileIP, const std::wstring& fileUse, const std::wstring& filePassword, std::wstring &AddFileToSqlResult) { return this->send_AddFileToSql(soap_endpoint_url, soap_action, serverInfo, strFileName, sPointer, tablenamefieldname, fileIP, fileUse, filePassword) || this->recv_AddFileToSql(AddFileToSqlResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_AddFileToSql' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_AddFileToSql(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strFileName, const std::wstring& sPointer, const std::wstring& tablenamefieldname, const std::wstring& fileIP, const std::wstring& fileUse, const std::wstring& filePassword);
        /// Web service asynchronous operation 'recv_AddFileToSql' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_AddFileToSql(std::wstring &AddFileToSqlResult);
        //
        /// Web service synchronous operation 'AddNumbers' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int AddNumbers_(int NumberOne, int NumberTwo, int &AddNumbersResult) { return this->AddNumbers_(NULL, NULL, NumberOne, NumberTwo, AddNumbersResult); }
        /// Web service synchronous operation 'AddNumbers' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int AddNumbers_(const char *soap_endpoint_url, const char *soap_action, int NumberOne, int NumberTwo, int &AddNumbersResult) { return this->send_AddNumbers_(soap_endpoint_url, soap_action, NumberOne, NumberTwo) || this->recv_AddNumbers_(AddNumbersResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_AddNumbers' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_AddNumbers_(const char *soap_endpoint_url, const char *soap_action, int NumberOne, int NumberTwo);
        /// Web service asynchronous operation 'recv_AddNumbers' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_AddNumbers_(int &AddNumbersResult);
        //
        /// Web service synchronous operation 'clearLink' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int clearLink_(bool bTimeContrl, std::wstring &clearLinkResult) { return this->clearLink_(NULL, NULL, bTimeContrl, clearLinkResult); }
        /// Web service synchronous operation 'clearLink' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int clearLink_(const char *soap_endpoint_url, const char *soap_action, bool bTimeContrl, std::wstring &clearLinkResult) { return this->send_clearLink_(soap_endpoint_url, soap_action, bTimeContrl) || this->recv_clearLink_(clearLinkResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_clearLink' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_clearLink_(const char *soap_endpoint_url, const char *soap_action, bool bTimeContrl);
        /// Web service asynchronous operation 'recv_clearLink' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_clearLink_(std::wstring &clearLinkResult);
        //
        /// Web service synchronous operation 'showExistLink' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int showExistLink_(std::wstring &showExistLinkResult) { return this->showExistLink_(NULL, NULL, showExistLinkResult); }
        /// Web service synchronous operation 'showExistLink' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int showExistLink_(const char *soap_endpoint_url, const char *soap_action, std::wstring &showExistLinkResult) { return this->send_showExistLink_(soap_endpoint_url, soap_action) || this->recv_showExistLink_(showExistLinkResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_showExistLink' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_showExistLink_(const char *soap_endpoint_url, const char *soap_action);
        /// Web service asynchronous operation 'recv_showExistLink' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_showExistLink_(std::wstring &showExistLinkResult);
        //
        /// Web service synchronous operation 'TestLinkSqlserver' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int TestLinkSqlserver_(const std::wstring& serverInfo, std::wstring &TestLinkSqlserverResult) { return this->TestLinkSqlserver_(NULL, NULL, serverInfo, TestLinkSqlserverResult); }
        /// Web service synchronous operation 'TestLinkSqlserver' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int TestLinkSqlserver_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, std::wstring &TestLinkSqlserverResult) { return this->send_TestLinkSqlserver_(soap_endpoint_url, soap_action, serverInfo) || this->recv_TestLinkSqlserver_(TestLinkSqlserverResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_TestLinkSqlserver' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_TestLinkSqlserver_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo);
        /// Web service asynchronous operation 'recv_TestLinkSqlserver' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_TestLinkSqlserver_(std::wstring &TestLinkSqlserverResult);
        //
        /// Web service synchronous operation 'executeSql' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_(const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSqlResult) { return this->executeSql_(NULL, NULL, serverInfo, sSql, executeSqlResult); }
        /// Web service synchronous operation 'executeSql' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSqlResult) { return this->send_executeSql_(soap_endpoint_url, soap_action, serverInfo, sSql) || this->recv_executeSql_(executeSqlResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeSql' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeSql_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql);
        /// Web service asynchronous operation 'recv_executeSql' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeSql_(std::wstring &executeSqlResult);
        //
        /// Web service synchronous operation 'executeSql_backEncord' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREbackEncord_(const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREbackEncordResult) { return this->executeSql_USCOREbackEncord_(NULL, NULL, serverInfo, sSql, executeSql_USCOREbackEncordResult); }
        /// Web service synchronous operation 'executeSql_backEncord' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREbackEncord_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREbackEncordResult) { return this->send_executeSql_USCOREbackEncord_(soap_endpoint_url, soap_action, serverInfo, sSql) || this->recv_executeSql_USCOREbackEncord_(executeSql_USCOREbackEncordResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeSql_backEncord' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeSql_USCOREbackEncord_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql);
        /// Web service asynchronous operation 'recv_executeSql_backEncord' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeSql_USCOREbackEncord_(std::wstring &executeSql_USCOREbackEncordResult);
        //
        /// Web service synchronous operation 'executeSql_encode' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREencode_(const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREencodeResult) { return this->executeSql_USCOREencode_(NULL, NULL, serverInfo, sSql, executeSql_USCOREencodeResult); }
        /// Web service synchronous operation 'executeSql_encode' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeSql_USCOREencode_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql, std::wstring &executeSql_USCOREencodeResult) { return this->send_executeSql_USCOREencode_(soap_endpoint_url, soap_action, serverInfo, sSql) || this->recv_executeSql_USCOREencode_(executeSql_USCOREencodeResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeSql_encode' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeSql_USCOREencode_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& sSql);
        /// Web service asynchronous operation 'recv_executeSql_encode' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeSql_USCOREencode_(std::wstring &executeSql_USCOREencodeResult);
        //
        /// Web service synchronous operation 'insertXml' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int insertXml_(const std::wstring& serverInfo, const std::wstring& strXml, bool encode, std::wstring &insertXmlResult) { return this->insertXml_(NULL, NULL, serverInfo, strXml, encode, insertXmlResult); }
        /// Web service synchronous operation 'insertXml' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int insertXml_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strXml, bool encode, std::wstring &insertXmlResult) { return this->send_insertXml_(soap_endpoint_url, soap_action, serverInfo, strXml, encode) || this->recv_insertXml_(insertXmlResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_insertXml' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_insertXml_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strXml, bool encode);
        /// Web service asynchronous operation 'recv_insertXml' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_insertXml_(std::wstring &insertXmlResult);
        //
        /// Web service synchronous operation 'executeStorageProcess' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int executeStorageProcess_(const std::wstring& serverInfo, const std::wstring& StorageProcessName, const std::wstring& Parameters, std::wstring &executeStorageProcessResult) { return this->executeStorageProcess_(NULL, NULL, serverInfo, StorageProcessName, Parameters, executeStorageProcessResult); }
        /// Web service synchronous operation 'executeStorageProcess' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int executeStorageProcess_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& StorageProcessName, const std::wstring& Parameters, std::wstring &executeStorageProcessResult) { return this->send_executeStorageProcess_(soap_endpoint_url, soap_action, serverInfo, StorageProcessName, Parameters) || this->recv_executeStorageProcess_(executeStorageProcessResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_executeStorageProcess' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_executeStorageProcess_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& StorageProcessName, const std::wstring& Parameters);
        /// Web service asynchronous operation 'recv_executeStorageProcess' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_executeStorageProcess_(std::wstring &executeStorageProcessResult);
        //
        /// Web service synchronous operation 'AddFileToSql' with default endpoint and default SOAP Action header, returns SOAP_OK or error code
        virtual int AddFileToSql_(const std::wstring& serverInfo, const std::wstring& strFileName, const std::wstring& sPointer, const std::wstring& tablenamefieldname, const std::wstring& fileIP, const std::wstring& fileUse, const std::wstring& filePassword, std::wstring &AddFileToSqlResult) { return this->AddFileToSql_(NULL, NULL, serverInfo, strFileName, sPointer, tablenamefieldname, fileIP, fileUse, filePassword, AddFileToSqlResult); }
        /// Web service synchronous operation 'AddFileToSql' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int AddFileToSql_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strFileName, const std::wstring& sPointer, const std::wstring& tablenamefieldname, const std::wstring& fileIP, const std::wstring& fileUse, const std::wstring& filePassword, std::wstring &AddFileToSqlResult) { return this->send_AddFileToSql_(soap_endpoint_url, soap_action, serverInfo, strFileName, sPointer, tablenamefieldname, fileIP, fileUse, filePassword) || this->recv_AddFileToSql_(AddFileToSqlResult) ? this->error : SOAP_OK; }
        /// Web service asynchronous operation 'send_AddFileToSql' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code
        virtual int send_AddFileToSql_(const char *soap_endpoint_url, const char *soap_action, const std::wstring& serverInfo, const std::wstring& strFileName, const std::wstring& sPointer, const std::wstring& tablenamefieldname, const std::wstring& fileIP, const std::wstring& fileUse, const std::wstring& filePassword);
        /// Web service asynchronous operation 'recv_AddFileToSql' to receive a response message from the connected endpoint, returns SOAP_OK or error code
        virtual int recv_AddFileToSql_(std::wstring &AddFileToSqlResult);
    };
#endif