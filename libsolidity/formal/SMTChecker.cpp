/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <libsolidity/formal/SMTChecker.h>

#include <libsolidity/ast/TypeProvider.h>
#include <libsolidity/formal/SMTPortfolio.h>
#include <libsolidity/formal/SymbolicTypes.h>

#include <libdevcore/StringUtils.h>

#include <boost/range/adaptor/map.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/optional.hpp>

using namespace std;
using namespace dev;
using namespace langutil;
using namespace dev::solidity;

SMTChecker::SMTChecker(ErrorReporter& _errorReporter, map<h256, string> const& _smtlib2Responses):
	m_bmc(m_context, _errorReporter, _smtlib2Responses),
	m_context(m_bmc.solver())
{
}

void SMTChecker::analyze(SourceUnit const& _source, shared_ptr<Scanner> const& _scanner)
{
	if (!_source.annotation().experimentalFeatures.count(ExperimentalFeature::SMTChecker))
		return;

	m_bmc.analyze(_source, _scanner);
}

vector<string> SMTChecker::unhandledQueries()
{
	return m_bmc.unhandledQueries();
}
