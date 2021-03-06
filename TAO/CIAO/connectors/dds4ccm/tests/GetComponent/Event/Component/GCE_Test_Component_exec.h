// -*- C++ -*-
// $Id: GCE_Test_Component_exec.h 90610 2010-06-15 18:03:17Z msmit $

#ifndef CIAO_COMPONENT_EXEC_H_
#define CIAO_COMPONENT_EXEC_H_

#include "GCE_Test_ComponentEC.h"

#include /**/ "Component_exec_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/LocalObject.h"

namespace CIAO_GCE_Test_GetComponentEventTestComponent_Impl
{
  //============================================================
  // Component_exec_i
  //============================================================
  class COMPONENT_EXEC_Export Component_exec_i
    : public virtual GetComponentEventTestComponent_Exec,
      public virtual ::CORBA::LocalObject
  {
  public:
    Component_exec_i (void);
    virtual ~Component_exec_i (void);

    ::CORBA::Boolean
    act_as_sender (void);

    void
    act_as_sender (::CORBA::Boolean act_as_sender);

    virtual ::GCETestConnector::CCM_Listener_ptr
    get_info_listen_data_listener (void);

    virtual ::CCM_DDS::CCM_PortStatusListener_ptr
    get_info_listen_status (void);

    virtual ::CCM_DDS::CCM_PortStatusListener_ptr
    get_info_get_status (void);

    virtual ::CCM_DDS::CCM_ConnectorStatusListener_ptr
    get_status_listener (void);

    // Operations from Components::SessionComponent.
    virtual void
    set_session_context (
      ::Components::SessionContext_ptr ctx);

    virtual void configuration_complete (void);

    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);
    virtual void ccm_remove (void);

  private:
    ::GCE_Test::CCM_GetComponentEventTestComponent_Context_var context_;
    ::CORBA::Boolean act_as_sender_;
    void test_writer (void);
    void test_getter (void);
    void test_listener (void);
  };

  extern "C" COMPONENT_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_GetComponentEventTest_Component_Impl (void);
}

#endif /* ifndef */

