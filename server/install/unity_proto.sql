
CREATE TABLE  %%cust_table%% (
  id int(10) unsigned NOT NULL auto_increment,
  kundenr varchar(100) NOT NULL default '',
  firma varchar(100) default '',
  navn varchar(100) NOT NULL default '',
  adresse varchar(100) NOT NULL default '',
  post varchar(10) NOT NULL default '0',
  `by` varchar(100) NOT NULL default '',
  tlf varchar(100) default '',
  mobil varchar(100) default '',
  fax varchar(100) default '',
  oprette date NOT NULL default '0000-00-00',
  mail varchar(100) default '',
  bemark text,
  EAN_SE varchar(100) default NULL,
  land varchar(100) default 'Danmark',
  PRIMARY KEY  (id),
  UNIQUE KEY  (kundenr)
) ENGINE=MyISAM;
--
-- Table structure for table 'Act_Conn'
--

CREATE TABLE Act_Conn (
  id int(10) unsigned NOT NULL auto_increment,
  cid varchar(15) NOT NULL default '',
  valid tinyint(1) NOT NULL default '0',
  user varchar(100) NOT NULL default '',
  PRIMARY KEY  (id)
) ENGINE=MyISAM;

--
-- Table structure for table 'Bruger'
--

CREATE TABLE Bruger (
  brugernavn varchar(100) NOT NULL default '',
  pass varchar(200) NOT NULL default '',
  brugernr int(2) NOT NULL default '0',
  tokalvl int(2) NOT NULL default '0',
  fnavn varchar(100) NOT NULL default '',
  enavn varchar(100) NOT NULL default '',
  tlf varchar(100) NOT NULL default '',
  mobil varchar(100) default '',
  mail varchar(100) default '',
  PRIMARY KEY  (brugernavn)
) ENGINE=MyISAM;

--
-- Table structure for table 'Extra_Data'
--

CREATE TABLE Extra_Data (
  id int(20) unsigned NOT NULL auto_increment,
  tilbud_nr int(11) NOT NULL default '0',
  lev_kunde text,
  bemark text,
  PRIMARY KEY  (id),
  UNIQUE KEY (tilbud_nr)
) ENGINE=MyISAM;

--
-- Table structure for table 'K-tilbud'
--

CREATE TABLE `K-tilbud` (
  linie_nr int(100) unsigned NOT NULL auto_increment,
  tilbud_nr int(10) unsigned NOT NULL default '0',
  type enum('T','O','K','A','S','X') default NULL,
  lev tinyint(1) NOT NULL default '0',
  reknr varchar(10) default '',
  kunde_nr varchar(100) NOT NULL default '',
  vare_nr varchar(100) default '',
  varetekst varchar(100) default '',
  stk int(5) default '0',
  pris double(8,2) default '0.00',
  rabat decimal(5,2) default '0.00',
  dato date default '2000-00-00',
  bemaerk text,
  lev_kunde text,
  tilstand varchar(100) default '',
  usr int(2) unsigned NOT NULL default '0',
  PRIMARY KEY  (linie_nr)
) ENGINE=MyISAM;

--
-- Table structure for table 'K_Sager'
--

CREATE TABLE K_Sager (
  id int(10) unsigned NOT NULL auto_increment,
  sagnr int(11) NOT NULL default '0',
  beskriv varchar(100) NOT NULL default '',
  pris double(8,2) NOT NULL default '0.00',
  PRIMARY KEY  (id),
  UNIQUE KEY (sagnr)
) ENGINE=MyISAM;

--
-- Table structure for table 'K_notat'
--

CREATE TABLE K_notat (
  notat_id int(20) unsigned NOT NULL auto_increment,
  titel varchar(100) NOT NULL default '',
  tekst text NOT NULL,
  k_id varchar(100) NOT NULL default '',
  dato date NOT NULL default '2000-00-00',
  ndato date default '2000-00-00',
  saelger_id varchar(100) NOT NULL default '',
  bruger varchar(100) default '',
  lukke_pro int(2) default '0',
  status enum('I','A') default 'I',
  lev enum('I','A') NOT NULL default 'I',
  internal_msg text,
  tilbud_nr int(11) default '0',
  tilbud_type enum('T','O','K','A','S','X') default NULL,
  PRIMARY KEY  (notat_id)
) ENGINE=MyISAM;

--
-- Table structure for table 'Maskiner'
--

CREATE TABLE Maskiner (
  id int(10) unsigned NOT NULL auto_increment,
  varenr varchar(100) NOT NULL default '',
  sort int(4) unsigned default '9999',
  varetekst varchar(100) default '',
  pris decimal(8,2) default '0.00',
  sidst_red date default '2000-01-01',
  PRIMARY KEY  (id)
) ENGINE=MyISAM;

--
-- Table structure for table 'Skurv'
--

CREATE TABLE Skurv (
  pri int(10) unsigned NOT NULL auto_increment,
  line int(10) unsigned NOT NULL default '0',
  id int(11) NOT NULL default '0',
  vareid varchar(20) NOT NULL default '0',
  varetext varchar(80) default NULL,
  stk int(5) NOT NULL default '0',
  rabat decimal(5,2) default '0.00',
  type enum('T','O','K','A','S') default NULL,
  pris decimal(8,2) default '0.00',
  PRIMARY KEY  (pri)
) ENGINE=MyISAM;

--
-- Table structure for table 'c_que'
--

CREATE TABLE c_que (
  id int(10) unsigned NOT NULL auto_increment,
  knr varchar(100) NOT NULL default '',
  name varchar(100) default NULL,
  att varchar(100) default NULL,
  adr varchar(100) NOT NULL default '',
  post varchar(20) NOT NULL default '',
  `by` varchar(60) NOT NULL default '',
  land varchar(100) NOT NULL default '',
  ean_se varchar(100) default NULL,
  tlf varchar(15) default NULL,
  fax varchar(15) default NULL,
  cell varchar(15) default NULL,
  PRIMARY KEY  (id),
  UNIQUE KEY  (knr)
) ENGINE=MyISAM;

--
-- Table structure for table 'calc'
--

CREATE TABLE calc (
  id int(100) unsigned NOT NULL auto_increment,
  tnr int(11) unsigned NOT NULL default '0',
  type enum('T','O','K','A') NOT NULL default 'T',
  ind_ud enum('S','SK','B','P','BK','SF','BF','K') NOT NULL default 'S',
  value varchar(100) default '',
  line int(11) unsigned default '0',
  PRIMARY KEY  (id)
) ENGINE=MyISAM;

--
-- Table structure for table 'k_oplysning'
--

CREATE TABLE k_oplysning (
  k_id varchar(100) NOT NULL default '',
  malke_k int(4) default '0',
  gold_k int(4) default '0',
  amme_k int(4) default '0',
  slagte_k int(4) default '0',
  fede_kalve int(4) default '0',
  faar int(4) default '0',
  andre varchar(100) default '',
  andre2 varchar(100) default '',
  dyrket_areal int(5) default '0',
  grovfoder varchar(100) default '',
  grovfoder1 varchar(100) default '',
  grovfoder2 varchar(100) default '',
  korn varchar(100) default '',
  korn1 varchar(100) default '',
  forrige_f_sy varchar(100) default '',
  forrige_f_ma varchar(100) default '',
  extra varchar(100) default '',
  extra1 varchar(100) default '',
  extra2 varchar(100) default '',
  PRIMARY KEY  (k_id)
) ENGINE=MyISAM;

--
-- Table structure for table 'lev_addr'
--

CREATE TABLE lev_addr (
  id int(11) unsigned NOT NULL auto_increment,
  navn varchar(100) NOT NULL default '',
  att varchar(100) NOT NULL default '',
  adresse1 varchar(100) NOT NULL default '',
  adresse2 varchar(100) default '',
  post varchar(10) NOT NULL default '0',
  `by` varchar(100) NOT NULL default '',
  oid int(11) NOT NULL default '0',
  PRIMARY KEY  (id),
  UNIQUE KEY  (oid)
) ENGINE=MyISAM;

--
-- Table structure for table 'mail_rules'
--

CREATE TABLE mail_rules (
  id int(10) unsigned NOT NULL auto_increment,
  active tinyint(1) unsigned NOT NULL default '0',
  type enum('T','O','K','A','S') NOT NULL default 'T',
  conditions varchar(10) NOT NULL default '',
  test_var varchar(50) default NULL,
  maillist text NOT NULL default '',
  PRIMARY KEY  (id)
) ENGINE=MyISAM;

--
-- Table structure for table 'multi_search'
--

CREATE TABLE multi_search (
  `key` int(50) unsigned NOT NULL auto_increment,
  `id` varchar(100) NOT NULL default '',
  `sql` text NOT NULL,
  PRIMARY KEY  (`key`)
) ENGINE=MyISAM;

--
-- Table structure for table 'nye_Sager'
--

CREATE TABLE nye_Sager (
  id int(10) unsigned NOT NULL auto_increment,
  type enum('S','H') default NULL,
  tidx int(10) unsigned default NULL,
  vnr varchar(100) default NULL,
  sagnr int(11) unsigned default NULL,
  beskriv varchar(100) default NULL,
  pris double(8,2) default NULL,
  PRIMARY KEY  (id),
  UNIQUE KEY  (sagnr)
) ENGINE=MyISAM;

--
-- Table structure for table 'preview'
--

CREATE TABLE preview (
  `key` int(50) unsigned NOT NULL auto_increment,
  id varchar(100) NOT NULL default '',
  onr int(15) NOT NULL default '0',
  PRIMARY KEY  (`key`)
) ENGINE=MyISAM;

--
-- Table structure for table 'stat_list'
--

CREATE TABLE stat_list (
  id int(100) unsigned NOT NULL auto_increment,
  uid varchar(50) NOT NULL default '',
  sid varchar(10) NOT NULL default '',
  `to` varchar(100) NOT NULL default '',
  `from` varchar(100) NOT NULL default '',
  PRIMARY KEY  (id)
) ENGINE=MyISAM;

--
-- Table structure for table 'tmp_files'
--

CREATE TABLE tmp_files (
  id int(100) unsigned NOT NULL auto_increment,
  `user` varchar(10) NOT NULL default '',
  title varchar(100) NOT NULL default '',
  file varchar(100) NOT NULL default '',
  PRIMARY KEY  (id)
) ENGINE=MyISAM;

--
-- Table structure for table 'used_mails'
--

CREATE TABLE used_mails (
  id int(10) unsigned NOT NULL auto_increment,
  `user` varchar(100) NOT NULL default '',
  mail varchar(100) NOT NULL default '',
  times int(100) unsigned NOT NULL default '0',
  PRIMARY KEY  (id)
) ENGINE=MyISAM;

