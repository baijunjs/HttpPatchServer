//
// impl/io_service.ipp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IMPL_IO_SERVICE_IPP
#define ASIO_IMPL_IO_SERVICE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "RCF/external/asio/asio/detail/config.hpp"
#include <boost/limits.hpp>
#include "RCF/external/asio/asio/io_service.hpp"
#include "RCF/external/asio/asio/detail/service_registry.hpp"
#include "RCF/external/asio/asio/detail/throw_error.hpp"

#if defined(ASIO_HAS_IOCP)
# include "RCF/external/asio/asio/detail/win_iocp_io_service.hpp"
#else
# include "RCF/external/asio/asio/detail/task_io_service.hpp"
#endif

#include "RCF/external/asio/asio/detail/push_options.hpp"

namespace asio {

io_service::io_service()
  : service_registry_(new asio::detail::service_registry(*this)),
    impl_(service_registry_->use_service<impl_type>())
{
  impl_.init((std::numeric_limits<std::size_t>::max)());
}

io_service::io_service(std::size_t concurrency_hint)
  : service_registry_(new asio::detail::service_registry(*this)),
    impl_(service_registry_->use_service<impl_type>())
{
  impl_.init(concurrency_hint);
}

io_service::~io_service()
{
  delete service_registry_;
}

std::size_t io_service::run()
{
  asio::error_code ec;
  std::size_t s = impl_.run(ec);
  asio::detail::throw_error(ec);
  return s;
}

std::size_t io_service::run(asio::error_code& ec)
{
  return impl_.run(ec);
}

std::size_t io_service::run_one()
{
  asio::error_code ec;
  std::size_t s = impl_.run_one(ec);
  asio::detail::throw_error(ec);
  return s;
}

std::size_t io_service::run_one(asio::error_code& ec)
{
  return impl_.run_one(ec);
}

std::size_t io_service::poll()
{
  asio::error_code ec;
  std::size_t s = impl_.poll(ec);
  asio::detail::throw_error(ec);
  return s;
}

std::size_t io_service::poll(asio::error_code& ec)
{
  return impl_.poll(ec);
}

std::size_t io_service::poll_one()
{
  asio::error_code ec;
  std::size_t s = impl_.poll_one(ec);
  asio::detail::throw_error(ec);
  return s;
}

std::size_t io_service::poll_one(asio::error_code& ec)
{
  return impl_.poll_one(ec);
}

void io_service::stop()
{
  impl_.stop();
}

void io_service::reset()
{
  impl_.reset();
}

io_service::service::service(asio::io_service& owner)
  : owner_(owner),
    next_(0)
{
}

io_service::service::~service()
{
}

service_already_exists::service_already_exists()
  : std::logic_error("Service already exists.")
{
}

invalid_service_owner::invalid_service_owner()
  : std::logic_error("Invalid service owner.")
{
}

} // namespace asio

#include "RCF/external/asio/asio/detail/pop_options.hpp"

#endif // ASIO_IMPL_IO_SERVICE_IPP
