/**
 * @author Marcel Smit (msmit@remedy.nl)
 *
 * $Id: DDS_TopicBase_Connector_T.h 96867 2013-02-27 08:21:02Z johnnyw $
 *
 * Wrapper facade for NDDS.
 */
#ifndef DDS_TOPICBASE_CONNECTOR_H
#define DDS_TOPICBASE_CONNECTOR_H

#include "ace/Copy_Disabled.h"

#include "dds4ccm/impl/DDS_Base_Connector_T.h"

template <typename CCM_TYPE, typename DDS_TYPE, typename SEQ_TYPE>
class DDS_TopicBase_Connector_T
  : public virtual DDS_Base_Connector_T<CCM_TYPE>
{
public:
  DDS_TopicBase_Connector_T (void);
  virtual ~DDS_TopicBase_Connector_T (void);

  virtual ::DDS::StringSeq *key_fields (void);

  virtual void topic_name (const char * topic_name);
  virtual char *topic_name (void);

  virtual void type_name (const char * type_name);
  virtual char *type_name (void);

  virtual void key_fields (const ::DDS::StringSeq & key_fields);

  virtual void configuration_complete (void);
  virtual void ccm_activate (void);
  virtual void ccm_passivate (void);
  virtual void ccm_remove (void);
  virtual void register_type (::DDS::DomainParticipant_ptr participant,
                              const char * typesupport_name);
  virtual
  void unregister_type (::DDS::DomainParticipant_ptr participant,
                        const char * typesupport_name);


protected:
  bool late_binding (void);
  void late_binding (bool late_binding);
  bool late_binded (const char * topic_name);
  bool stop_dds (const char * topic_name);

  CORBA::String_var topic_name_;
  CORBA::String_var type_name_;
  DDS::StringSeq key_fields_;

  ::DDS::Topic_var topic_;
  ::DDS::TopicListener_var topiclistener_;

  ::DDS::Publisher_var publisher_;
  ::DDS::PublisherListener_var publisher_listener_;
  ::DDS::Subscriber_var subscriber_;
  ::DDS::SubscriberListener_var subscriber_listener_;

  bool init_subscriber_;
  bool init_publisher_;

  typedef DDS_Base_Connector_T<CCM_TYPE> BaseConnector;

#if (CIAO_DDS4CCM_NDDS==1)
  typedef ::CIAO::NDDS::DDS_TypeFactory_T <DDS_TYPE, SEQ_TYPE> dds_type_factory;
#endif

private:
  bool late_binding_;
};

#include "dds4ccm/impl/DDS_TopicBase_Connector_T.cpp"

#endif /* DDS_TOPICBASE_CONNECTOR_H */
