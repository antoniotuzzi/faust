/*

  Copyright (C) 2011 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <sstream>
#include "deelx.h"
#include "htmlpage.h"
#include "jsscripts.h"
#include "stylesheet.h"

using namespace std;

void find_and_replace(string &source, const string find, string replace ) {

	size_t j;
	for ( ; (j = source.find( find )) != string::npos ; ) {
		source.replace( j, find.length(), replace );
	}
}

namespace httpdfaust
{

static const char * kPortNumberHandler = "__port_number__handler__";

//--------------------------------------------------------------------------
htmlpage::htmlpage(const char *name, const char* address, int port) 
					: fName(name), fAddress(address), fPort(port)
{
}

//--------------------------------------------------------------------------
string htmlpage::getUrl() const
{
	stringstream url;
	url << "http://" << fAddress << ":" << kPortNumberHandler;
	return url.str();
}

//--------------------------------------------------------------------------
void htmlpage::print(std::ostream& out) const
{
	if (false) {
		out << "<html>\n<head>\n";
		out << "	<link id='css' rel='stylesheet' type='text/css' href='css/style1.css' />\n";
		out << "	<script src='js/jquery-1.7.1.min.js' language='javascript'></script>\n";
		out << "	<script src='js/faust.js' language='javascript'></script>\n";
		out << "	<title id=titre>" << fName << "</title>";
		out << "</head>\n<body>\n";
		out << "<script>\n\tfunction setStyle(num) { $(\"#css\").attr('href','css/style'+num+'.css');}";
		out << "\n</script>\n";
		out << "<center>\n\n";
	} else {
		out << "<html>\n<head>\n";
		out << "	<link id='css' rel='stylesheet' type='text/css' href='http://faust.grame.fr/userinterface/css/style1.css' />\n";
		out << "	<script src='http://faust.grame.fr/userinterface/js/jquery-1.7.1.min.js' language='javascript'></script>\n";
		out << "	<script src='http://faust.grame.fr/userinterface/js/faust.js' language='javascript'></script>\n";
		out << "	<title id=titre>" << fName << "</title>";
		out << "</head>\n<body>\n";
		out << "<script>\n\tfunction setStyle(num) { $(\"#css\").attr('href','http://faust.grame.fr/userinterface/css/style'+num+'.css');}";
		out << "\n</script>\n";
		out << "<center>\n\n";
	}
	
	out << "<input type='hidden' id='root' value='" << fRoot << "'>\n";
	out << "<table class='ui'>\n";
	out << "<tr><td class='name'>karplus</td>\n";
	out << "<td class='url'>" << fAddress << "</td>\n";
	out << "<td class='port'>: " << fPort << "</td>\n";
	out << "</tr>\n";
	out << "<tr><td colspan=3 class='sep'><hr/></td></tr>\n";

#if 0
	stringstream port;
	port << fPort;
	CRegexpT<char> regexp (kPortNumberHandler);
	out << regexp.Replace(this->str().c_str(), port.str().c_str());
#else
	out << this->str();		// the ui itself, generated byt htmlfactory
#endif

	out << "<tr><td colspan=3 class='sep'><hr/></td></tr>\n";
	out << "</table>\n\n";
	
	out << "<div id='style'>Style:\n";
	out << "	<input type='radio' id='style1' name='style' value=1 checked onclick= setStyle(this.value) >\n";
	out << "	<input type='radio' id='style2' name='style' value=2 onclick= setStyle(this.value) >\n";
	out << "</div>\n";
	out << "</center></body>\n</html>\n";
}

//--------------------------------------------------------------------------
void htmlpage::print(std::ostream& out, string s) const
{
	(void) find_and_replace(s, "\n", " ");
	(void) find_and_replace(s, "\t", " ");
	(void) find_and_replace(s, "'", "&rsquo;");
	out << "<html>" << endl;
	out << "  <head>" << endl;
    
#ifdef LOADSCRIPTS
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/jquery-1.7.1.min.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/jquerysvg/jquery.svg.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/jquerysvg/jquery.svgdom.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_proto.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_mobile.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_ui_inits.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_load_external_file.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_ui_objects.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_ui_builder.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_ui_interact.js\"></script>" << endl;
	out << "    <script type=\"text/javascript\" src=\"http://www.mikesolomon.org/faust/svg/faust_server_communication.js\"></script>" << endl;
	out << "    <link rel=\"stylesheet\" type=\"text/css\" href=\"http://www.mikesolomon.org/faust/svg/faust_css.css\"></link>" << endl;
#else
	out << "<style type=\"text/css\">" << endl;
        for (unsigned int i=0; i < stylesheet_len; i++) { out << stylesheet[i]; } out << endl;
    out << "</style>" << endl;

    out << "    <script type=\"text/javascript\" >" << endl;
        for (unsigned int i=0; i < jsscripts_len; i++) { out << jsscripts[i]; } out << endl;
    out << "    </script>" << endl;
#endif

	out << "  </head>" << endl;
	out << "  <body>" << endl;
	out << "    <div id=\"faustsvg\">" << endl;
	out << "    </div>" << endl;
	out << "    <script type=\"text/javascript\">" << endl;
	out << "      $('#faustsvg').svg({onLoad: function (svg) {" << endl;
	out << "        _f4u$t.main(svg, '";
	out << s;
	out << "');" << endl;
	out << "      }});" << endl;
	out << "    </script>" << endl;
	out << "  </body>" << endl;
	out << "</html>";
}

} // end namespoace
