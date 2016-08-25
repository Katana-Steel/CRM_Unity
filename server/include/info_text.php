<?php
/**************************************************************************
    This file: ../web/helhed/include/info_text.php is part of Helhed Client.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
?>
<?php
	switch($type)
	{
	case "S":
	    $t = split(";",$time);
		$ret =  "Herunder er jeres forventninger til salg af maskiner i perioden: <u>".
		        date("d/m Y",$t[0]) . "</u> - <u>" . date("d/m Y",$t[1]) ."</u>";
		break;
	case "O":
		$ret =  "Idet vi takker for Deres ordre, skal det hermed for god ordens skyld bekr&aelig;ftes, at De ".
				"ved aftale den<br> <u>". date("d/m Y",$time) ."</u> p&aring; de nedenst&aring;ende og p&aring; de vedh&aelig;ftet ".
				"anf&oslash;rte almindelige salgs- og leveringsbetingelser<br> har k&oslash;bt f&oslash;lgende n&aelig;rmere ".
				"specificerede genstande til levering ab fabrik - medmindre andet skriftligt er<br> aftalt.";
		break;
	case "T":
		$ret = "Idet vi takker for Deres interesse, skal det hermed for god ordens skyld bekr&aelig;ftes, ".
		       "at De, den ". date("d/m Y",$time) .", har<br> modtaget et tilbud p&aring nedenst&aring;ende. Ved h&aelig;ftet ".
		       "p&aring; mailen er der anf&oslash;rt almindelige salgs- og leveringsbetingelser<br> forbundet ved ".
		       "k&oslash;b af nedenst&aring;ende n&aelig;rmere specificerede genstande. Tilbudet er som standard g&aelig;ldende ".
		       "<br>i 10 arbejdsdage - medmindre andet skriftligt er aftalt.";
		break;
	case "K":
		$ret = "Vi leverer med s&aelig;dvanligt ejendomsforbehold til konsignataren ".
		       "f&oslash;lgende varer:";
		break;
	}
?>
