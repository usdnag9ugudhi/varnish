# Contributing to Vinyl Cache

The official development tree is here: <https://code.vinyl-cache.org/vinyl-cache/vinyl-cache>

We prefer patches as [pull requests](https://code.vinyl-cache.org/vinyl-cache/vinyl-cache/compare/main) onto the ``main`` branch.

Please use [issues](https://code.vinyl-cache.org/vinyl-cache/vinyl-cache/issues/new/choose) for bug reports.

Our main project communication is through our developer IRC channel ``#vinyl-hacking`` on server irc.linpro.no

(That channel is not for user questions, use the ``#vinyl-cache`` channel for that.)

Mondays at 15:00 EU time we hold our weekly "bugwash" where we go
through new (and old) tickets.  It speeds things up a lot if you
can join the channel and answer questions directly when we go over
the ticket.

See [Developing for and with Vinyl Cache](https://vinyl-cache.org/developer/index.html) for additional information.

## General process

In general, please follow these steps when contributing new features or
non-trivial fixes:

1) Present the idea on -dev or in an issue
2) Write the documentation and present it
3) Create the full PR

## [Pull Requests](https://code.vinyl-cache.org/vinyl-cache/vinyl-cache/pulls)

Pull requests are handled like other tickets.

Trivial pull requests (fix typos, etc) are welcomed, but they may be committed
by a core team member and the author credited in the commit message.

For anything non trivial, please take [Jens Axboe's excellent contributing
guide](https://github.com/axboe/liburing/blob/master/CONTRIBUTING.md) as
guidance.

Notable differences for Vinyl Cache are:

* For code style, we broadly follow bsd [style(9)](https://man.freebsd.org/cgi/man.cgi?query=style&sektion=9)

* Regarding commit messages, we are usually less strict

* The Vinyl Cache repository uses a linear history, so all changes are rebased
  on top of the current upstream head always. When your PR can no longer be
  merged, rebase it and force-push your changes.

* For testing ``make distcheck`` should pass
