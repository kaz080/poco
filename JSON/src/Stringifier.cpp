//
// Stringifier.cpp
//
// $Id$
//
// Library: JSON
// Package: JSON
// Module:  Stringifier
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/JSON/Stringifier.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Object.h"
#include <iomanip>


using Poco::Dynamic::Var;


namespace Poco {
namespace JSON {


void Stringifier::stringify(const Var& any, std::ostream& out, unsigned int indent, int step, bool preserveInsertionOrder)
{
	if (step == -1) step = indent;

	if ( any.type() == typeid(Object) )
	{
		const Object& o = any.extract<Object>();
		o.stringify(out, indent == 0 ? 0 : indent, step);
	}
	else if ( any.type() == typeid(Array) )
	{
		const Array& a = any.extract<Array>();
		a.stringify(out, indent == 0 ? 0 : indent, step);
	}
	else if ( any.type() == typeid(Object::Ptr) )
	{
		const Object::Ptr& o = any.extract<Object::Ptr>();
		o->stringify(out, indent == 0 ? 0 : indent, step);
	}
	else if ( any.type() == typeid(Array::Ptr) )
	{
		const Array::Ptr& a = any.extract<Array::Ptr>();
		a->stringify(out, indent == 0 ? 0 : indent, step);
	}
	else if ( any.isEmpty() )
	{
		out << "null";
	}
	else if ( any.isString() )
	{
		std::string value = any.convert<std::string>();
		formatString(value, out);
	}
	else
	{
		out << any.convert<std::string>();
	}
}


void Stringifier::formatString(const std::string& value, std::ostream& out)
{
	out << '"';
	for (std::string::const_iterator it = value.begin(); it != value.end(); ++it)
	{
		switch (*it)
		{
		case '"':
			out << "\\\"";
			break;
		case '\\':
			out << "\\\\";
			break;
		case '\b':
			out << "\\b";
			break;
		case '\f':
			out << "\\f";
			break;
		case '\n':
			out << "\\n";
			break;
		case '\r':
			out << "\\r";
			break;
		case '\t':
			out << "\\t";
			break;
		default:
		{
			if ( *it > 0 && *it <= 0x1F )
			{
				out << "\\u" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << static_cast<int>(*it);
			}
			else
			{
				out << *it;
			}
			break;
		}
		}
	}
	out << '"';
}

} }  // Namespace Poco::JSON
