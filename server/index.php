<?php
function svg_corner($h, $w, $r, $outer, $left) {
    echo ("      <svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"${h}\" width=\"${w}\">\n");
    $class = ($outer) ? "outer " : "inner";
    echo ("       <rect height=\"${h}\" width=\"${w}\" class=\"${class}\" />\n");
    $cx = ($left) ? $w : 0;
    echo ("       <circle cx=\"${cx}\" cy=\"${h}\" r=\"${r}\" class=\"${class}\" />\n");
    echo ("      </svg>\n");
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
  <head>
    <meta http-equiv="Content-Language" content="en" />
    <meta http-equiv="Content-Type" content="application/xhtml-xml; charset=UTF-8" />
    <title>Alchemiestick CRM - Unity</title>
    <link rel="stylesheet" href="style/style_inst.css" type="text/css" />
    <script src="js/ajax.js" type="text/javascript"></script>
    <script src="js/ajax-dynamic-content.js" type="text/javascript"></script>
    <script src="js/form.js" type="text/javascript"></script>
  </head>
<body class="inner">
<table width="100%" height="100%" border="0px" cellpadding="0px" cellspacing="0px">
  <tr>
    <td class="corner outer">
<?php svg_corner(15,15,15,1,1); ?>
    </td>
    <td colspan="3" class="outer title">&nbsp;</td>
  </tr>
  <tr>
    <td class="outer">&nbsp;</td>
    <td colspan="3" class="outer title">Unity Installer/Setup checker</td>
  </tr>
  <tr>
    <td class="outer">&nbsp;</td>
    <td class="corner inner">
<?php svg_corner(15,15,15,0,1); ?>
    </td>
    <td class="inner" style="max-height:15px;">&nbsp;</td>
  </tr>
  <tr>
    <td class="outer menu" valign="top">
      <div id="mmm"></div>
    </td>
    <td class="inner">&nbsp;</td>
    <td class="inner pbody" valign="top">
      <div id="main_body"></div>
    </td>
  </tr>
  <tr valign="bottom">
    <td class="outer">&nbsp;</td>
    <td align="center" class="inner" colspan="3" style="font-size: 10px;">
      <div id="license"></div>
    </td>
  </tr>
</table>
<?php
  $main = "greet.php";
?>
<script type="text/javascript" language="javascript">
enableCache=false;
ajax_loadContent('mmm', 'menu.php');
ajax_loadContent('license','blank.php');
ajax_loadContent('main_body','<?= $main ?>?tz='+ new Date().toLocaleString());
</script>
</body>
</html>
