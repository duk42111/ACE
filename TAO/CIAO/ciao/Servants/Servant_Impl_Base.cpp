// $Id: Servant_Impl_Base.cpp 94919 2011-11-01 11:00:10Z mcorino $

#include "Servant_Impl_Base.h"

#include "ciao/Logger/Log_Macros.h"

namespace CIAO
{
  Servant_Impl_Base::Servant_Impl_Base (Components::CCMHome_ptr home,
                                        Home_Servant_Impl_Base *home_servant,
                                        Container_ptr c)
    : Connector_Servant_Impl_Base (home, home_servant, c)
  {
  }

  Servant_Impl_Base::~Servant_Impl_Base (void)
  {
  }

  void
  Servant_Impl_Base::remove (void)
  {
    CIAO_TRACE("Servant_Impl_Base::remove (void)");
#if !defined (CCM_NOEVENT)

    try
    {
      Container_var cnt_safe =
        Container::_duplicate(this->container_.in ());
      PortableServer::POA_var port_poa =
        this->container_->the_port_POA ();

      for (ConsumerTable::const_iterator iter =
             this->consumer_table_.begin ();
           iter != this->consumer_table_.end ();
           ++iter)
        {
          PortableServer::ObjectId_var cons_id =
            port_poa->reference_to_id (iter->second);

          port_poa->deactivate_object (cons_id);
        }
    }
    catch (const CORBA::Exception& ex)
    {
      // log error and propagate so error gets reported to deployment framework
      CIAO_ERROR (1, (LM_ERROR, CLINFO "Servant_Impl_Base::remove - CORBA exception : %C\n", ex._info ().c_str ()));
      ex._raise (); // propagate
    }
#endif

    /// This call deactivates facets, removes executor and home
    /// servant (if any), and uninstalls us from the container.
    /// It has its own try/catch blocks.
    this->Connector_Servant_Impl_Base::remove ();
  }

#if !defined (CCM_LW)
  ::Components::ComponentPortDescription *
  Servant_Impl_Base::get_all_ports (void)
  {
    CIAO_TRACE("Servant_Impl_Base::get_all_ports (void)");

    ::Components::ComponentPortDescription_var retv =
      this->Connector_Servant_Impl_Base::get_all_ports ();
#if !defined (CCM_NOEVENT)
    ::Components::ConsumerDescriptions_var consumer_desc =
      this->get_all_consumers ();

    ::Components::EmitterDescriptions_var emitter_desc =
      this->get_all_emitters ();

    ::Components::PublisherDescriptions_var publisher_desc =
      this->get_all_publishers ();

    retv->consumers (consumer_desc.in ());
    retv->emitters (emitter_desc.in ());
    retv->publishers (publisher_desc.in ());
#endif
    return retv._retn ();
  }
#endif

#if !defined (CCM_LW)
  ::Components::PrimaryKeyBase *
  Servant_Impl_Base::get_primary_key (void)
  {
    CIAO_TRACE("Servant_Impl_Base::get_primary_key");
    throw ::Components::NoKeyAvailable ();
  }
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  ::Components::ConsumerDescriptions *
  Servant_Impl_Base::get_all_consumers (void)
  {
    CIAO_TRACE("Servant_Impl_Base::get_all_consumers (void)");

    ::Components::ConsumerDescriptions *tmp = 0;
    ACE_NEW_THROW_EX (tmp,
                      ::Components::ConsumerDescriptions (
                      this->consumer_table_.size ()),
                      CORBA::NO_MEMORY ());

    ::Components::ConsumerDescriptions_var retval = tmp;

    retval->length (this->consumer_table_.size ());
    CORBA::ULong i = 0UL;

    for (ConsumerTable::const_iterator iter =
           this->consumer_table_.begin ();
         iter != this->consumer_table_.end ();
         ++iter, ++i)
      {
        ::Components::ConsumerDescription *cd = 0;
        ACE_NEW_THROW_EX (cd,
                          ::OBV_Components::ConsumerDescription,
                          CORBA::NO_MEMORY ());

        cd->name (iter->first.c_str ());
        cd->type_id (iter->second->_interface_repository_id ());
        cd->consumer (iter->second);

        retval[i] = cd;
      }

    return retval._retn ();
  }
#endif
#if !defined (CCM_NOEVENT)
  ::Components::EventConsumerBase_ptr
  Servant_Impl_Base::get_consumer (const char *sink_name)
  {
    CIAO_TRACE("Servant_Impl_Base::get_consumer (const char *sink_name)");

    if (sink_name == 0)
      {
        throw ::CORBA::BAD_PARAM ();
      }

    ::Components::EventConsumerBase_ptr retval =
      this->lookup_consumer (sink_name);

    if (::CORBA::is_nil (retval))
      {
        throw ::Components::InvalidName ();
      }

    return retval;
  }
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  ::Components::ConsumerDescriptions *
  Servant_Impl_Base::get_named_consumers (
    const ::Components::NameList & names)
  {
    CIAO_TRACE("Servant_Impl_Base::get_named_consumers");

    Components::ConsumerDescriptions *retval = 0;
    ACE_NEW_THROW_EX (retval,
                    ::Components::ConsumerDescriptions,
                      CORBA::NO_MEMORY ());

    Components::ConsumerDescriptions_var safe_retval = retval;
    CORBA::ULong const len = names.length ();
    safe_retval->length (len);

    for (CORBA::ULong i = 0; i < len; ++i)
      {
        ::Components::ConsumerDescription *tmp =
          this->lookup_consumer_description (names[i]);

        if (tmp == 0)
          {
            throw ::Components::InvalidName ();
          }

        safe_retval[i] = tmp;
      }

    return safe_retval._retn ();
  }
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  ::Components::EmitterDescriptions *
  Servant_Impl_Base::get_named_emitters (
      const ::Components::NameList & names)
  {
    CIAO_TRACE("Servant_Impl_Base::get_named_emitters");
    ::Components::EmitterDescriptions *retval = 0;
    ACE_NEW_THROW_EX (retval,
                      ::Components::EmitterDescriptions,
                      ::CORBA::NO_MEMORY ());

    ::Components::EmitterDescriptions_var safe_retval = retval;
    const ::CORBA::ULong len = names.length ();
    safe_retval->length (len);

    for (::CORBA::ULong i = 0UL; i < len; ++i)
      {
        ::Components::EmitterDescription * desc =
          this->lookup_emitter_description (names[i].in ());
        if (desc)
          {
            safe_retval[i] = desc;
          }
        else
          {
            throw ::Components::InvalidName ();
          }
      }
    return safe_retval._retn ();
  }
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  ::Components::PublisherDescriptions *
  Servant_Impl_Base::get_named_publishers (
    const ::Components::NameList & names)
  {
    CIAO_TRACE("Servant_Impl_Base::get_named_publishers");
    ::Components::PublisherDescriptions_var retval;
    ACE_NEW_THROW_EX (retval,
                      ::Components::PublisherDescriptions,
                      ::CORBA::NO_MEMORY ());

    retval->length (names.length ());
    ::CORBA::ULong count = 0UL;

    for (::CORBA::ULong name = 0UL;
         name < names.length ();
         ++name)
      {
        ::Components::PublisherDescription * desc =
          this->lookup_publisher_description (names[name].in ());
        if (desc)
          {
            retval[count++] = desc;
          }
        else
          {
            throw ::Components::InvalidName ();
          }
      }
    ::Components::PublisherDescriptions_var safe_retval = retval;
    return safe_retval._retn ();
  }
#endif

  /// Protected operations.
#if  !defined (CCM_NOEVENT)
  void
  Servant_Impl_Base::add_consumer (const char *port_name,
                                   ::Components::EventConsumerBase_ptr port_ref)
  {
    CIAO_TRACE("Servant_Impl_Base::add_consumer");

    if (0 == port_name || ::CORBA::is_nil (port_ref))
      {
        CIAO_ERROR (1,
                    (LM_ERROR,
                     CLINFO
                     "Servant_Impl_Base::add_consumer - Bad port name [%C] or bad objref\n",
                     port_name));

        throw ::CORBA::BAD_PARAM ();
      }

    {
      ACE_GUARD_THROW_EX (TAO_SYNCH_MUTEX,
                          mon,
                          this->lock_,
                          CORBA::NO_RESOURCES ());

      this->consumer_table_[port_name] = ::Components::EventConsumerBase::_duplicate (port_ref);
    }
  }
#endif

#if !defined (CCM_NOEVENT)
  ::Components::EventConsumerBase_ptr
  Servant_Impl_Base::lookup_consumer (const char *port_name)
  {
    CIAO_TRACE("Servant_Impl_Base::lookup_consumer");

    if (0 == port_name)
      {
        return ::Components::EventConsumerBase::_nil ();
      }

    ACE_GUARD_THROW_EX (TAO_SYNCH_MUTEX,
                        mon,
                        this->lock_,
                        CORBA::NO_RESOURCES ());

    ConsumerTable::const_iterator iter =
      this->consumer_table_.find (port_name);

    if (iter == this->consumer_table_.end ())
      {
        return ::Components::EventConsumerBase::_nil ();
      }

    return ::Components::EventConsumerBase::_duplicate (iter->second);
  }
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  ::Components::ConsumerDescription *
  Servant_Impl_Base::lookup_consumer_description (
    const char *port_name)
  {
    CIAO_TRACE("Servant_Impl_Base::lookup_consumer_description");

    if (0 == port_name)
      {
        /// Calling function will throw InvalidName after getting this.
        return 0;
      }

    ::Components::ConsumerDescription_var cd;
    ConsumerTable::const_iterator iter;

    {
      ACE_GUARD_THROW_EX (TAO_SYNCH_MUTEX,
                          mon,
                          this->lock_,
                          CORBA::NO_RESOURCES ());

      iter = this->consumer_table_.find (port_name);

      if (iter != this->consumer_table_.end ())
        {
          ::Components::ConsumerDescription *cdp = 0;
          ACE_NEW_THROW_EX (cdp,
                            ::OBV_Components::ConsumerDescription,
                            CORBA::NO_MEMORY ());

          cdp->name (iter->first.c_str ());
          cdp->type_id (iter->second->_interface_repository_id ());
          cdp->consumer (iter->second);
          cd = cdp;
        }
    }

    return cd._retn ();
  }
#endif

  /// Private operations.
#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  ::Components::PublisherDescription *
  Servant_Impl_Base::lookup_publisher_description (const char *publisher_name)
  {
    CIAO_TRACE("Servant_Impl_Base::lookup_publisher_description");

    ::Components::PublisherDescriptions_var all_publishers =
      this->get_all_publishers ();

    if (!publisher_name || all_publishers->length () == 0)
      {
        // Calling function will throw InvalidName after getting this.
        return 0;
      }
    for (::CORBA::ULong publisher = 0;
          publisher < all_publishers->length ();
          ++publisher)
      {
        ::Components::PublisherDescription *publisher_desc =
          all_publishers[publisher];
        if (::ACE_OS::strcmp (publisher_name, publisher_desc->name ()) == 0)
          {
            ::Components::PublisherDescription *pd = 0;
            ACE_NEW_THROW_EX (pd,
                              ::OBV_Components::PublisherDescription (),
                              CORBA::NO_MEMORY ());
            pd->name (publisher_desc->name ());
            pd->type_id (publisher_desc->type_id ());
            pd->consumers (publisher_desc->consumers ());
            ::Components::PublisherDescription_var safe = pd;
            return safe._retn ();
          }
      }
    return 0;
  }
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  ::Components::EmitterDescription *
  Servant_Impl_Base::lookup_emitter_description (const char *emitter_name)
  {
    CIAO_TRACE("Servant_Impl_Base::lookup_emitter_description");

    ::Components::EmitterDescriptions_var all_emitters =
      this->get_all_emitters ();

    if (!emitter_name || all_emitters->length () == 0)
      {
        // Calling function will throw InvalidName after getting this.
        return 0;
      }
    for (::CORBA::ULong emitter = 0;
          emitter < all_emitters->length ();
          ++emitter)
      {
        ::Components::EmitterDescription *emitter_desc =
          all_emitters[emitter];
        if (::ACE_OS::strcmp (emitter_name, emitter_desc->name ()) == 0)
          {
            ::Components::EmitterDescription *ed = 0;

            ACE_NEW_THROW_EX (ed,
                              ::OBV_Components::EmitterDescription (),
                              CORBA::NO_MEMORY ());

            ed->name (emitter_desc->name ());
            ed->type_id (emitter_desc->type_id ());
            ed->consumer (emitter_desc->consumer());

           ::Components::EmitterDescription_var safe = ed;

            return safe._retn ();
          }
      }
    return 0;
  }
#endif

}

