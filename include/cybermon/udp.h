
////////////////////////////////////////////////////////////////////////////
//
// UDP processing
//
////////////////////////////////////////////////////////////////////////////

#ifndef CYBERMON_UDP_H
#define CYBERMON_UDP_H

#include <cybermon/context.h>
#include <cybermon/manager.h>
#include <cybermon/udp_ports.h>


namespace cybermon {
    
    // A UDP context.
    class udp_context : public context {
      public:

    // Once identified, the processing function.
    process_fn processor;

    // Constructor, when specifying flow address and parent context.
    udp_context(manager& m, const flow_address& a, context_ptr p)
        : context(m)
    { 
        addr = a;
        parent = p; 

        // Only need to initialise handlers once
        if (!is_udp_handlers_init())
        {
            init_udp_handlers();
        }
    }

	// Type is "udp".
	virtual std::string get_type() { return "udp"; }

	typedef boost::shared_ptr<udp_context> ptr;

	static context_ptr create(manager& m, const flow_address& f, 
				  context_ptr par)
    {
	    context_ptr cp = context_ptr(new udp_context(m, f, par));
	    return cp;
	}

	// Given a flow address, returns the child context.
	static ptr get_or_create(context_ptr base, const flow_address& f) {
	    context_ptr cp = context::get_or_create(base, f, 
						    udp_context::create);
	    ptr sp = boost::dynamic_pointer_cast<udp_context>(cp);
	    return sp;
	}

    };
    
    class udp {

      public:
	
	// UDP processing.
	static void process(manager& mgr, context_ptr c, pdu_iter s, 
			    pdu_iter e);

    };

};

#endif

