#include "stdafx.h"
#using <mscorlib.dll>
#using <System.dll>
#using <System.Xml.dll>
#using <System.Web.Services.dll>
#using <System.EnterpriseServices.dll>
#using <System.Data.dll>
using namespace System::Net;

using namespace System::Security::Permissions;
[assembly:SecurityPermissionAttribute(SecurityAction::RequestMinimum, SkipVerification=false)];
// 
// 此源代码由 wsdl 自动生成, Version=2.0.50727.3038。
// 
using namespace System::Xml::Serialization;
using namespace System::Web::Services;
using namespace System::ComponentModel;
using namespace System::Web::Services::Protocols;
using namespace System;
using namespace System::Diagnostics;
using namespace System::Data;
using namespace System;
ref class WeatherWebService;
ref class getSupportCityCompletedEventArgs;
ref class getSupportProvinceCompletedEventArgs;
ref class getSupportDataSetCompletedEventArgs;
ref class getWeatherbyCityNameCompletedEventArgs;
ref class getWeatherbyCityNameProCompletedEventArgs;


/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038")]
public delegate System::Void getSupportCityCompletedEventHandler(System::Object^  sender, getSupportCityCompletedEventArgs^  e);

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038")]
public delegate System::Void getSupportProvinceCompletedEventHandler(System::Object^  sender, getSupportProvinceCompletedEventArgs^  e);

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038")]
public delegate System::Void getSupportDataSetCompletedEventHandler(System::Object^  sender, getSupportDataSetCompletedEventArgs^  e);

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038")]
public delegate System::Void getWeatherbyCityNameCompletedEventHandler(System::Object^  sender, getWeatherbyCityNameCompletedEventArgs^  e);

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038")]
public delegate System::Void getWeatherbyCityNameProCompletedEventHandler(System::Object^  sender, getWeatherbyCityNameProCompletedEventArgs^  e);

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038"), 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code"), 
System::Web::Services::WebServiceBindingAttribute(Name=L"WeatherWebServiceSoap", Namespace=L"http://WebXml.com.cn/")]
public ref class WeatherWebService : public System::Web::Services::Protocols::SoapHttpClientProtocol {

private: System::Threading::SendOrPostCallback^  getSupportCityOperationCompleted;

private: System::Threading::SendOrPostCallback^  getSupportProvinceOperationCompleted;

private: System::Threading::SendOrPostCallback^  getSupportDataSetOperationCompleted;

private: System::Threading::SendOrPostCallback^  getWeatherbyCityNameOperationCompleted;

private: System::Threading::SendOrPostCallback^  getWeatherbyCityNameProOperationCompleted;

		 /// <remarks/>
public: event getSupportCityCompletedEventHandler^  getSupportCityCompleted;

		/// <remarks/>
public: event getSupportProvinceCompletedEventHandler^  getSupportProvinceCompleted;

		/// <remarks/>
public: event getSupportDataSetCompletedEventHandler^  getSupportDataSetCompleted;

		/// <remarks/>
public: event getWeatherbyCityNameCompletedEventHandler^  getWeatherbyCityNameCompleted;

		/// <remarks/>
public: event getWeatherbyCityNameProCompletedEventHandler^  getWeatherbyCityNameProCompleted;

		/// <remarks/>
public: WeatherWebService();
		/// <remarks/>
public: [System::Web::Services::Protocols::SoapDocumentMethodAttribute(L"http://WebXml.com.cn/getSupportCity", RequestNamespace=L"http://WebXml.com.cn/", 
			ResponseNamespace=L"http://WebXml.com.cn/", Use=System::Web::Services::Description::SoapBindingUse::Literal, ParameterStyle=System::Web::Services::Protocols::SoapParameterStyle::Wrapped)]
		cli::array< System::String^  >^  getSupportCity(System::String^  byProvinceName);

		/// <remarks/>
public: System::IAsyncResult^  BegingetSupportCity(System::String^  byProvinceName, System::AsyncCallback^  callback, 
			System::Object^  asyncState);

		/// <remarks/>
public: cli::array< System::String^  >^  EndgetSupportCity(System::IAsyncResult^  asyncResult);

		/// <remarks/>
public: System::Void getSupportCityAsync(System::String^  byProvinceName);

		/// <remarks/>
public: System::Void getSupportCityAsync(System::String^  byProvinceName, System::Object^  userState);

private: System::Void OngetSupportCityOperationCompleted(System::Object^  arg);

		 /// <remarks/>
public: [System::Web::Services::Protocols::SoapDocumentMethodAttribute(L"http://WebXml.com.cn/getSupportProvince", RequestNamespace=L"http://WebXml.com.cn/", 
			ResponseNamespace=L"http://WebXml.com.cn/", Use=System::Web::Services::Description::SoapBindingUse::Literal, ParameterStyle=System::Web::Services::Protocols::SoapParameterStyle::Wrapped)]
		cli::array< System::String^  >^  getSupportProvince();

		/// <remarks/>
public: System::IAsyncResult^  BegingetSupportProvince(System::AsyncCallback^  callback, System::Object^  asyncState);

		/// <remarks/>
public: cli::array< System::String^  >^  EndgetSupportProvince(System::IAsyncResult^  asyncResult);

		/// <remarks/>
public: System::Void getSupportProvinceAsync();

		/// <remarks/>
public: System::Void getSupportProvinceAsync(System::Object^  userState);

private: System::Void OngetSupportProvinceOperationCompleted(System::Object^  arg);

		 /// <remarks/>
public: [System::Web::Services::Protocols::SoapDocumentMethodAttribute(L"http://WebXml.com.cn/getSupportDataSet", RequestNamespace=L"http://WebXml.com.cn/", 
			ResponseNamespace=L"http://WebXml.com.cn/", Use=System::Web::Services::Description::SoapBindingUse::Literal, ParameterStyle=System::Web::Services::Protocols::SoapParameterStyle::Wrapped)]
		System::Data::DataSet^  getSupportDataSet();

		/// <remarks/>
public: System::IAsyncResult^  BegingetSupportDataSet(System::AsyncCallback^  callback, System::Object^  asyncState);

		/// <remarks/>
public: System::Data::DataSet^  EndgetSupportDataSet(System::IAsyncResult^  asyncResult);

		/// <remarks/>
public: System::Void getSupportDataSetAsync();

		/// <remarks/>
public: System::Void getSupportDataSetAsync(System::Object^  userState);

private: System::Void OngetSupportDataSetOperationCompleted(System::Object^  arg);

		 /// <remarks/>
public: [System::Web::Services::Protocols::SoapDocumentMethodAttribute(L"http://WebXml.com.cn/getWeatherbyCityName", RequestNamespace=L"http://WebXml.com.cn/", 
			ResponseNamespace=L"http://WebXml.com.cn/", Use=System::Web::Services::Description::SoapBindingUse::Literal, ParameterStyle=System::Web::Services::Protocols::SoapParameterStyle::Wrapped)]
		cli::array< System::String^  >^  getWeatherbyCityName(System::String^  theCityName);

		/// <remarks/>
public: System::IAsyncResult^  BegingetWeatherbyCityName(System::String^  theCityName, System::AsyncCallback^  callback, 
			System::Object^  asyncState);

		/// <remarks/>
public: cli::array< System::String^  >^  EndgetWeatherbyCityName(System::IAsyncResult^  asyncResult);

		/// <remarks/>
public: System::Void getWeatherbyCityNameAsync(System::String^  theCityName);

		/// <remarks/>
public: System::Void getWeatherbyCityNameAsync(System::String^  theCityName, System::Object^  userState);

private: System::Void OngetWeatherbyCityNameOperationCompleted(System::Object^  arg);

		 /// <remarks/>
public: [System::Web::Services::Protocols::SoapDocumentMethodAttribute(L"http://WebXml.com.cn/getWeatherbyCityNamePro", RequestNamespace=L"http://WebXml.com.cn/", 
			ResponseNamespace=L"http://WebXml.com.cn/", Use=System::Web::Services::Description::SoapBindingUse::Literal, ParameterStyle=System::Web::Services::Protocols::SoapParameterStyle::Wrapped)]
		cli::array< System::String^  >^  getWeatherbyCityNamePro(System::String^  theCityName, System::String^  theUserID);

		/// <remarks/>
public: System::IAsyncResult^  BegingetWeatherbyCityNamePro(System::String^  theCityName, System::String^  theUserID, 
			System::AsyncCallback^  callback, System::Object^  asyncState);

		/// <remarks/>
public: cli::array< System::String^  >^  EndgetWeatherbyCityNamePro(System::IAsyncResult^  asyncResult);

		/// <remarks/>
public: System::Void getWeatherbyCityNameProAsync(System::String^  theCityName, System::String^  theUserID);

		/// <remarks/>
public: System::Void getWeatherbyCityNameProAsync(System::String^  theCityName, System::String^  theUserID, System::Object^  userState);

private: System::Void OngetWeatherbyCityNameProOperationCompleted(System::Object^  arg);

		 /// <remarks/>
public: System::Void CancelAsync(System::Object^  userState) new;

public: System::Void SetUrl(System::String^ strUrl);
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038"), 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code")]
public ref class getSupportCityCompletedEventArgs : public System::ComponentModel::AsyncCompletedEventArgs {

private: cli::array< System::Object^  >^  results;

internal: getSupportCityCompletedEventArgs(cli::array< System::Object^  >^  results, System::Exception^  exception, System::Boolean cancelled, 
			  System::Object^  userState);
		  /// <remarks/>
public: property cli::array< System::String^  >^  Result {
			cli::array< System::String^  >^  get();
		}
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038"), 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code")]
public ref class getSupportProvinceCompletedEventArgs : public System::ComponentModel::AsyncCompletedEventArgs {

private: cli::array< System::Object^  >^  results;

internal: getSupportProvinceCompletedEventArgs(cli::array< System::Object^  >^  results, System::Exception^  exception, 
			  System::Boolean cancelled, System::Object^  userState);
		  /// <remarks/>
public: property cli::array< System::String^  >^  Result {
			cli::array< System::String^  >^  get();
		}
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038"), 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code")]
public ref class getSupportDataSetCompletedEventArgs : public System::ComponentModel::AsyncCompletedEventArgs {

private: cli::array< System::Object^  >^  results;

internal: getSupportDataSetCompletedEventArgs(cli::array< System::Object^  >^  results, System::Exception^  exception, 
			  System::Boolean cancelled, System::Object^  userState);
		  /// <remarks/>
public: property System::Data::DataSet^  Result {
			System::Data::DataSet^  get();
		}
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038"), 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code")]
public ref class getWeatherbyCityNameCompletedEventArgs : public System::ComponentModel::AsyncCompletedEventArgs {

private: cli::array< System::Object^  >^  results;

internal: getWeatherbyCityNameCompletedEventArgs(cli::array< System::Object^  >^  results, System::Exception^  exception, 
			  System::Boolean cancelled, System::Object^  userState);
		  /// <remarks/>
public: property cli::array< System::String^  >^  Result {
			cli::array< System::String^  >^  get();
		}
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"wsdl", L"2.0.50727.3038"), 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code")]
public ref class getWeatherbyCityNameProCompletedEventArgs : public System::ComponentModel::AsyncCompletedEventArgs {

private: cli::array< System::Object^  >^  results;

internal: getWeatherbyCityNameProCompletedEventArgs(cli::array< System::Object^  >^  results, System::Exception^  exception, 
			  System::Boolean cancelled, System::Object^  userState);
		  /// <remarks/>
public: property cli::array< System::String^  >^  Result {
			cli::array< System::String^  >^  get();
		}
};


inline WeatherWebService::WeatherWebService() {
	this->Url = L"http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
}

inline System::Void WeatherWebService::SetUrl(System::String^ strUrl)
{
	this->Url = strUrl;
}

inline cli::array< System::String^  >^  WeatherWebService::getSupportCity(System::String^  byProvinceName) {
	cli::array< System::Object^  >^  results = this->Invoke(L"getSupportCity", gcnew cli::array< System::Object^  >(1) {byProvinceName});
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::IAsyncResult^  WeatherWebService::BegingetSupportCity(System::String^  byProvinceName, System::AsyncCallback^  callback, 
																	 System::Object^  asyncState) {
																		 return this->BeginInvoke(L"getSupportCity", gcnew cli::array< System::Object^  >(1) {byProvinceName}, callback, asyncState);
}

inline cli::array< System::String^  >^  WeatherWebService::EndgetSupportCity(System::IAsyncResult^  asyncResult) {
	cli::array< System::Object^  >^  results = this->EndInvoke(asyncResult);
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::Void WeatherWebService::getSupportCityAsync(System::String^  byProvinceName) {
	this->getSupportCityAsync(byProvinceName, nullptr);
}

inline System::Void WeatherWebService::getSupportCityAsync(System::String^  byProvinceName, System::Object^  userState) {
	if (this->getSupportCityOperationCompleted == nullptr) {
		this->getSupportCityOperationCompleted = gcnew System::Threading::SendOrPostCallback(this, &WeatherWebService::OngetSupportCityOperationCompleted);
	}
	this->InvokeAsync(L"getSupportCity", gcnew cli::array< System::Object^  >(1) {byProvinceName}, this->getSupportCityOperationCompleted, 
		userState);
}

inline System::Void WeatherWebService::OngetSupportCityOperationCompleted(System::Object^  arg) {
	{
		System::Web::Services::Protocols::InvokeCompletedEventArgs^  invokeArgs = (cli::safe_cast<System::Web::Services::Protocols::InvokeCompletedEventArgs^  >(arg));
		this->getSupportCityCompleted(this, (gcnew getSupportCityCompletedEventArgs(invokeArgs->Results, invokeArgs->Error, invokeArgs->Cancelled, 
			invokeArgs->UserState)));
	}
}

inline cli::array< System::String^  >^  WeatherWebService::getSupportProvince() {
	cli::array< System::Object^  >^  results = this->Invoke(L"getSupportProvince", gcnew cli::array< System::Object^  >(0));
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::IAsyncResult^  WeatherWebService::BegingetSupportProvince(System::AsyncCallback^  callback, System::Object^  asyncState) {
	return this->BeginInvoke(L"getSupportProvince", gcnew cli::array< System::Object^  >(0), callback, asyncState);
}

inline cli::array< System::String^  >^  WeatherWebService::EndgetSupportProvince(System::IAsyncResult^  asyncResult) {
	cli::array< System::Object^  >^  results = this->EndInvoke(asyncResult);
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::Void WeatherWebService::getSupportProvinceAsync() {
	this->getSupportProvinceAsync(nullptr);
}

inline System::Void WeatherWebService::getSupportProvinceAsync(System::Object^  userState) {
	if (this->getSupportProvinceOperationCompleted == nullptr) {
		this->getSupportProvinceOperationCompleted = gcnew System::Threading::SendOrPostCallback(this, &WeatherWebService::OngetSupportProvinceOperationCompleted);
	}
	this->InvokeAsync(L"getSupportProvince", gcnew cli::array< System::Object^  >(0), this->getSupportProvinceOperationCompleted, 
		userState);
}

inline System::Void WeatherWebService::OngetSupportProvinceOperationCompleted(System::Object^  arg) {
	{
		System::Web::Services::Protocols::InvokeCompletedEventArgs^  invokeArgs = (cli::safe_cast<System::Web::Services::Protocols::InvokeCompletedEventArgs^  >(arg));
		this->getSupportProvinceCompleted(this, (gcnew getSupportProvinceCompletedEventArgs(invokeArgs->Results, invokeArgs->Error, 
			invokeArgs->Cancelled, invokeArgs->UserState)));
	}
}

inline System::Data::DataSet^  WeatherWebService::getSupportDataSet() {
	cli::array< System::Object^  >^  results = this->Invoke(L"getSupportDataSet", gcnew cli::array< System::Object^  >(0));
	return (cli::safe_cast<System::Data::DataSet^  >(results[0]));
}

inline System::IAsyncResult^  WeatherWebService::BegingetSupportDataSet(System::AsyncCallback^  callback, System::Object^  asyncState) {
	return this->BeginInvoke(L"getSupportDataSet", gcnew cli::array< System::Object^  >(0), callback, asyncState);
}

inline System::Data::DataSet^  WeatherWebService::EndgetSupportDataSet(System::IAsyncResult^  asyncResult) {
	cli::array< System::Object^  >^  results = this->EndInvoke(asyncResult);
	return (cli::safe_cast<System::Data::DataSet^  >(results[0]));
}

inline System::Void WeatherWebService::getSupportDataSetAsync() {
	this->getSupportDataSetAsync(nullptr);
}

inline System::Void WeatherWebService::getSupportDataSetAsync(System::Object^  userState) {
	if (this->getSupportDataSetOperationCompleted == nullptr) {
		this->getSupportDataSetOperationCompleted = gcnew System::Threading::SendOrPostCallback(this, &WeatherWebService::OngetSupportDataSetOperationCompleted);
	}
	this->InvokeAsync(L"getSupportDataSet", gcnew cli::array< System::Object^  >(0), this->getSupportDataSetOperationCompleted, 
		userState);
}

inline System::Void WeatherWebService::OngetSupportDataSetOperationCompleted(System::Object^  arg) {
	{
		System::Web::Services::Protocols::InvokeCompletedEventArgs^  invokeArgs = (cli::safe_cast<System::Web::Services::Protocols::InvokeCompletedEventArgs^  >(arg));
		this->getSupportDataSetCompleted(this, (gcnew getSupportDataSetCompletedEventArgs(invokeArgs->Results, invokeArgs->Error, 
			invokeArgs->Cancelled, invokeArgs->UserState)));
	}
}

inline cli::array< System::String^  >^  WeatherWebService::getWeatherbyCityName(System::String^  theCityName) {
	cli::array< System::Object^  >^  results = this->Invoke(L"getWeatherbyCityName", gcnew cli::array< System::Object^  >(1) {theCityName});
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::IAsyncResult^  WeatherWebService::BegingetWeatherbyCityName(System::String^  theCityName, System::AsyncCallback^  callback, 
																		   System::Object^  asyncState) {
																			   return this->BeginInvoke(L"getWeatherbyCityName", gcnew cli::array< System::Object^  >(1) {theCityName}, callback, asyncState);
}

inline cli::array< System::String^  >^  WeatherWebService::EndgetWeatherbyCityName(System::IAsyncResult^  asyncResult) {
	cli::array< System::Object^  >^  results = this->EndInvoke(asyncResult);
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::Void WeatherWebService::getWeatherbyCityNameAsync(System::String^  theCityName) {
	this->getWeatherbyCityNameAsync(theCityName, nullptr);
}

inline System::Void WeatherWebService::getWeatherbyCityNameAsync(System::String^  theCityName, System::Object^  userState) {
	if (this->getWeatherbyCityNameOperationCompleted == nullptr) {
		this->getWeatherbyCityNameOperationCompleted = gcnew System::Threading::SendOrPostCallback(this, &WeatherWebService::OngetWeatherbyCityNameOperationCompleted);
	}
	this->InvokeAsync(L"getWeatherbyCityName", gcnew cli::array< System::Object^  >(1) {theCityName}, this->getWeatherbyCityNameOperationCompleted, 
		userState);
}

inline System::Void WeatherWebService::OngetWeatherbyCityNameOperationCompleted(System::Object^  arg) {
	{
		System::Web::Services::Protocols::InvokeCompletedEventArgs^  invokeArgs = (cli::safe_cast<System::Web::Services::Protocols::InvokeCompletedEventArgs^  >(arg));
		this->getWeatherbyCityNameCompleted(this, (gcnew getWeatherbyCityNameCompletedEventArgs(invokeArgs->Results, invokeArgs->Error, 
			invokeArgs->Cancelled, invokeArgs->UserState)));
	}
}

inline cli::array< System::String^  >^  WeatherWebService::getWeatherbyCityNamePro(System::String^  theCityName, System::String^  theUserID) {
	cli::array< System::Object^  >^  results = this->Invoke(L"getWeatherbyCityNamePro", gcnew cli::array< System::Object^  >(2) {theCityName, 
		theUserID});
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::IAsyncResult^  WeatherWebService::BegingetWeatherbyCityNamePro(System::String^  theCityName, System::String^  theUserID, 
																			  System::AsyncCallback^  callback, System::Object^  asyncState) {
																				  return this->BeginInvoke(L"getWeatherbyCityNamePro", gcnew cli::array< System::Object^  >(2) {theCityName, theUserID}, callback, 
																					  asyncState);
}

inline cli::array< System::String^  >^  WeatherWebService::EndgetWeatherbyCityNamePro(System::IAsyncResult^  asyncResult) {
	cli::array< System::Object^  >^  results = this->EndInvoke(asyncResult);
	return (cli::safe_cast<cli::array< System::String^  >^  >(results[0]));
}

inline System::Void WeatherWebService::getWeatherbyCityNameProAsync(System::String^  theCityName, System::String^  theUserID) {
	this->getWeatherbyCityNameProAsync(theCityName, theUserID, nullptr);
}

inline System::Void WeatherWebService::getWeatherbyCityNameProAsync(System::String^  theCityName, System::String^  theUserID, 
																	System::Object^  userState) {
																		if (this->getWeatherbyCityNameProOperationCompleted == nullptr) {
																			this->getWeatherbyCityNameProOperationCompleted = gcnew System::Threading::SendOrPostCallback(this, &WeatherWebService::OngetWeatherbyCityNameProOperationCompleted);
																		}
																		this->InvokeAsync(L"getWeatherbyCityNamePro", gcnew cli::array< System::Object^  >(2) {theCityName, theUserID}, this->getWeatherbyCityNameProOperationCompleted, 
																			userState);
}

inline System::Void WeatherWebService::OngetWeatherbyCityNameProOperationCompleted(System::Object^  arg) {
	{
		System::Web::Services::Protocols::InvokeCompletedEventArgs^  invokeArgs = (cli::safe_cast<System::Web::Services::Protocols::InvokeCompletedEventArgs^  >(arg));
		this->getWeatherbyCityNameProCompleted(this, (gcnew getWeatherbyCityNameProCompletedEventArgs(invokeArgs->Results, invokeArgs->Error, 
			invokeArgs->Cancelled, invokeArgs->UserState)));
	}
}

inline System::Void WeatherWebService::CancelAsync(System::Object^  userState) {
	__super::CancelAsync(userState);
}


inline getSupportCityCompletedEventArgs::getSupportCityCompletedEventArgs(cli::array< System::Object^  >^  results, System::Exception^  exception, 
																		  System::Boolean cancelled, System::Object^  userState) : 
System::ComponentModel::AsyncCompletedEventArgs(exception, cancelled, userState) {
	this->results = results;
}

inline cli::array< System::String^  >^  getSupportCityCompletedEventArgs::Result::get() {
	this->RaiseExceptionIfNecessary();
	return (cli::safe_cast<cli::array< System::String^  >^  >(this->results[0]));
}


inline getSupportProvinceCompletedEventArgs::getSupportProvinceCompletedEventArgs(cli::array< System::Object^  >^  results, 
																				  System::Exception^  exception, System::Boolean cancelled, System::Object^  userState) : 
System::ComponentModel::AsyncCompletedEventArgs(exception, cancelled, userState) {
	this->results = results;
}

inline cli::array< System::String^  >^  getSupportProvinceCompletedEventArgs::Result::get() {
	this->RaiseExceptionIfNecessary();
	return (cli::safe_cast<cli::array< System::String^  >^  >(this->results[0]));
}


inline getSupportDataSetCompletedEventArgs::getSupportDataSetCompletedEventArgs(cli::array< System::Object^  >^  results, 
																				System::Exception^  exception, System::Boolean cancelled, System::Object^  userState) : 
System::ComponentModel::AsyncCompletedEventArgs(exception, cancelled, userState) {
	this->results = results;
}

inline System::Data::DataSet^  getSupportDataSetCompletedEventArgs::Result::get() {
	this->RaiseExceptionIfNecessary();
	return (cli::safe_cast<System::Data::DataSet^  >(this->results[0]));
}


inline getWeatherbyCityNameCompletedEventArgs::getWeatherbyCityNameCompletedEventArgs(cli::array< System::Object^  >^  results, 
																					  System::Exception^  exception, System::Boolean cancelled, System::Object^  userState) : 
System::ComponentModel::AsyncCompletedEventArgs(exception, cancelled, userState) {
	this->results = results;
}

inline cli::array< System::String^  >^  getWeatherbyCityNameCompletedEventArgs::Result::get() {
	this->RaiseExceptionIfNecessary();
	return (cli::safe_cast<cli::array< System::String^  >^  >(this->results[0]));
}


inline getWeatherbyCityNameProCompletedEventArgs::getWeatherbyCityNameProCompletedEventArgs(cli::array< System::Object^  >^  results, 
																							System::Exception^  exception, System::Boolean cancelled, System::Object^  userState) : 
System::ComponentModel::AsyncCompletedEventArgs(exception, cancelled, userState) {
	this->results = results;
}

inline cli::array< System::String^  >^  getWeatherbyCityNameProCompletedEventArgs::Result::get() {
	this->RaiseExceptionIfNecessary();
	return (cli::safe_cast<cli::array< System::String^  >^  >(this->results[0]));
}


std::wstring  g_GetWeather( CString strCity )
{
	WeatherWebService ^wsService =gcnew WeatherWebService();
	std::wstring strResult;
	wsService->SetUrl(L"http://www.webxml.com.cn/WebServices/WeatherWebService.asmx");

	System::String^ _strCity =gcnew System::String(strCity.GetString());
	array<System::String ^> ^data = wsService->getWeatherbyCityName(_strCity);
	System::String ^strWh = L"";
	for (int i=0;i<data->Length;i++)
	{
		strWh += data[i];
		strWh +=" ";
	}
	cli::array<wchar_t>^ bytes = strWh->ToCharArray();
	pin_ptr<wchar_t> pinned = &bytes[0];
		
	strResult.assign((wchar_t*)pinned,bytes->Length);
	return strResult;
}
