.. role:: ref(emphasis)

.. _varnishlog-json(1):

===============
varnishlog-json
===============

-----------------------------------
Display Varnish logs in JSON format
-----------------------------------

:Manual section: 1

SYNOPSIS
========

.. include:: ../include/varnishlog-json_synopsis.rst
varnishlog |synopsis|

DESCRIPTION
===========

``varnishlog-json`` is a log reader similar to ``varnishlog`` or
``varnishncsa``, reading the varnishd(1) shared memory logs and presenting
them in a standardized ``JSON`` format.

``varnishlog`` provides all the records pertaining to a transaction, which can
be too much, while ``varnishncsa`` only presents the headers and data that were
specifically targeted by its format string, making it easy to miss unplanned
information. ``varnishlog-json`` tries to strike a balance between the too by
offering a fixed ``JSON`` schema, capturing the request/response as it it sent
to or received from the peer.

For example, when reporting on a backend transaction, it will ignore modifications made to ``bereq`` after it was sent, and on the client side, it will ignore any changes the ``VCL`` makes to the request.

Similar to how ``varnishncsa`` behaves, ``ESI`` and backend transactions are ignored by default.

The following options are available:

.. include:: ../include/varnishlog-json_options.rst

JSON STRUCTURE
==============

``varnishlog-json`` gets its data from the same source as ``varnishlog``, so
it's important to understand which tags are used to produce the output. It can
be particularly useful if you want to suppress part of the object using the
``-i/-I/-x/-X`` arguments.

We'll use ``typescript`` notation to describe the object shape:

::

  {
      req: {                                      // describes the request as seen by the remote (either client, or backend)
          headers: Map<string, string>,           // keys (header names) are lowercase, this map is built using ReqHeader,
                                                  // BereqHeader, RespUnset, and BerespUnset tags
          method: string,                         // ReqMethod, BereqMethod
          proto: string,                          // ReqProtocol, BereqProtocol
          hdrBytes: number,                       // ReqAcct, BereqAcct
          bodyBytes: number,                      // ^ same
      },
      resp: {                                     // describes the remote as seen by the remote
          headers: Map<string, string>,           // keys (header names) are lowercase, uses ReqHeader,
                                                  //   BereqHeader, RespUnset, and BerespUnset
          set-cookie?: Array<string>,             // Set-Cookie headers
          proto: string,                          // RespProtocol, BerespProtocol
          status: number,                         // RespStatus, BerespStatus
          reason: string,                         // RespReason, BerespReason,
          hdrBytes: number,                       // ReqAcct, BereqAcct
          bodyBytes: number,                      // ^ same
      },
      handling: "hit" | "miss" | "pass" |"pipe" |
                "streaming-hit" | "fail" | "synth"
                "abandon" | "fetch" | "error",    // how the request was handled, using VCL_call records, notably
      timeline: Array<{name: string,
                       timestamp: number}>        // Timestamp records
      side: "backend" | "client",
      id: string,                                 // the transaction's vxid
      vcl: string                                 // VCL_use
      client?: {                                  // ReqStar (client-side only)
          rAddr: string,
          rPort: number,
          sock: string,
      },
      backend?: {                                 // BackendOpen (backend-side only)
          name: string,                           // the name is simplified to the director name for udo/goto backends
          rAddr: string,
          rPort: number,
          connReused: bool,
      },
      storage?: string,                           // Storage (backend-only)
      errors?: Array<string>,                     // Error, VCL_Error, FetchError, if the VSL transaction was incomplete
      logs: Array<string>,                        // VCL_Log
      links: Array<{                              // Link
          type: string,
          id: string,
          reason: string,
      }>,
  }

If you use `-g request`, instead of one object per line, `varnishlog-json` will out an array of all objects in the group.

SIGNALS
=======

* SIGUSR1

  Flush any outstanding transactions

SEE ALSO
========
* :ref:`varnishd(1)`
* :ref:`varnishhist(1)`
* :ref:`varnishlog(1)`
* :ref:`varnishncsa(1)`
* :ref:`varnishstat(1)`
* :ref:`varnishtop(1)`
* :ref:`vsl(7)`
* :ref:`vsl-query(7)`
