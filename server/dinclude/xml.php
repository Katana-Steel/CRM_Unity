<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml.php is part of Helhed Server.

    Helhed Server is free software: you can redistribute it and/or modify
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
<? 
class vare {
	function vare($s) { $this->type = $s; }
	var $type;
	var $stk;
	var $vid;
	var $vtxt;
	var $pris;
	var $rab;
}

class XMLParser {
	var $type;
	var $gross;
	var $i;
	var $kid;
	var $cdata;
	var $cJourSQL;
	var $cOrdHead;
	var $cLevAddr;
	var $disSQL;
	var $cusm;
	var $klar;
	var $lev;
	var $parser;
	var $bemark;
	var $ret;
	var $brg;
	var $link;
	var $clear;
	var $period;

	function xml_tag_data($parser, $data) {
		$this->cdata .= unicode($data);
	}
	
	function xml_start_tag($parser, $name, $attr) {
		switch($name) {
			case "T":
			case "O":
			case "K":
			case "A":
			case "S":
				$this->type = $name;
				$this->cJourSQL .= "tilbud_type='$this->type',";
				$this->cOrdHead .= "type='$this->type',";
				break;
			case "salg":
				$this->gross[] = new vare("S");
				break;
			case "byt":
				$this->gross[] = new vare("B"); 
				$this->gross[$this->i]->rab = "NULL";
				break;
			case "disable":
				$this->disSQL = "update `K_notat` set status='I' where ";
				break;
			case "bemark":
				$this->clear = false;
				$this->cdata = "";
				break;
			case "b":
				if(!$this->clear) {
				  $this->cdata .= "<b>";
				}
				break;
			case "i":
				if(!$this->clear) {
				  $this->cdata .= "<i>";
				}
				break;
		}
		if($this->clear) $this->cdata = "";
	}

	function xml_end_tag($parser, $name) {
		switch($name) {
			case "salg":
			case "byt":
				$this->i++;
				break;
			case "stk":
				if( $this->cdata != "") $this->gross[$this->i]->stk = $this->cdata;
				break;
			case "nr":
				if( $this->cdata != "") $this->gross[$this->i]->vid = $this->cdata;
				break;
			case "txt":
				if( $this->cdata != "") $this->gross[$this->i]->vtxt = $this->cdata;
				break;
			case "pris":
				if( $this->cdata != "") $this->gross[$this->i]->pris = $this->cdata;
				break;
			case "rabat":
				if( $this->cdata != "") $this->gross[$this->i]->rab = $this->cdata;
				break;
			case "rek_nr":
				if( $this->cdata != "") $this->cOrdHead .= "reknr='$this->cdata',";
				break;
			case "luk":
				if( $this->cdata != "") $this->cJourSQL .= "lukke_pro=$this->cdata,";
				break;
			case "int_msg":
				if( $this->cdata != "") $this->cJourSQL .= "internal_msg='$this->cdata',";
				break;
			case "kid":
				echo "kid: " . $this->cdata . "\n";
				if( $this->cdata != "") { 
					$this->cJourSQL .= "k_id=$this->cdata,";
					$this->cOrdHead .= "kunde_nr='".$this->cdata."',";
					$this->kid = $this->cdata;
				}
				break;
			case "email":
				if( $this->cdata != "" ) $this->cusm = split('[,;]',$this->cdata);
				break;
			case "klar":
				if( $this->cdata == "true" ) $this->klar = true;
				break;
			case "lev_beta":
				if( $this->cdata != "" ) $this->cOrdHead .= "lev_kunde='$this->cdata',";
				break;
			case "bemark":
				if( $this->cdata != "" ) { 
					$this->bemark = $this->cdata;
				}
				$this->clear = true;
				break;
			case "b":
				if(!$this->clear) {
				  $this->cdata .= "</b>";
				}
				break;
			case "i":
				if(!$this->clear) {
				  $this->cdata .= "</i>";
				}
				break;
			case "br":
				if(!$this->clear) {
				  $this->cdata .= "\n";
				}
				break;
			case "niv":
				if( $this->cdata != "" ) { 
					$this->cOrdHead .= "usr=$this->cdata,";
					$this->cJourSQL .= "bruger=$this->cdata,";
					$this->brg = $this->cdata;
				}
				break;
			case "lev_navn":
				if( $this->cdata != "" ) {
					if(!$this->lev) $this->cOrdHead .= "lev=1,";
					$this->lev = true;
					$this->cLevAddr .= "navn='$this->cdata',";
				}	
				break;
			case "lev_att":
				if( $this->cdata != "" ) {
					if(!$this->lev) $this->cOrdHead .= "lev=1,";
					$this->lev = true;
					$this->cLevAddr .= "att='$this->cdata',";
				}	
				break;
			case "lev_adr":
				if( $this->cdata != "" ) {
					if(!$this->lev) $this->cOrdHead .= "lev=1,";
					$this->lev = true;
					$this->cLevAddr .= "adresse1='$this->cdata',";
				}	
				break;
			case "lev_post":
				if( $this->cdata != "" ) {
					if(!$this->lev) $this->cOrdHead .= "lev=1,";
					$this->lev = true;
					$this->cLevAddr .= "post='$this->cdata',";
				}	
				break;
			case "lev_by":
				if( $this->cdata != "" ) {
					if(!$this->lev) $this->cOrdHead .= "lev=1,";
					$this->lev = true;
					$this->cLevAddr .= "`by`='$this->cdata',";
				}	
				break;
			case "ndato":
				$this->cJourSQL .= "ndato='$this->cdata',";
				break;
			case "period":
				$this->period = $this->cdata;
				break;
			case "disable":
				$this->disSQL .= "notat_id=".$this->cdata;
				break;
		}
	}

	function XMLParser($usr,$fl,$link) {
		$this->i = 0;
		$this->link = $link;
		$this->klar = false;
		$this->lev = false;
		$this->gross = array();
		$this->type = "None";
		$this->clear = true;
		$this->cJourSQL = "insert into K_notat set saelger_id='$usr',dato=NOW(),status='A',";
		$this->cOrdHead = "insert into `K-tilbud` set dato=NOW(),";
		$this->cLevAddr = "insert into lev_addr set ";
		$this->parser = xml_parser_create();
		xml_set_object($this->parser,$this);
		xml_parser_set_option($this->parser,XML_OPTION_CASE_FOLDING,false);
		xml_set_element_handler($this->parser,"xml_start_tag","xml_end_tag");
		xml_set_character_data_handler($this->parser,"xml_tag_data");
		$data = file_get_contents($fl);
		$data = str_replace("<br>","\n",$data);
		$data = str_replace("&amp;","\303\123",$data);
		$data = str_replace(" & "," \303\123 ",$data);
		$data = str_replace("&","",$data);
		$data = str_replace("\303\123","&amp;",$data);
		$data = unicode($data);
		$tmpfname = tempnam("/var/www", "FOO");
		echo $tmpfname . "\n";
		$handle = fopen($tmpfname, "w");
		fwrite($handle, $data);
		fclose($handle);
		$this->ret = xml_parse($this->parser,$data,true);
//		unlink($fl);
	}
}
?>
