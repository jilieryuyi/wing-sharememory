--TEST--
Check for wing_sharememory presence
--SKIPIF--
<?php if (!extension_loaded("wing_sharememory")) print "skip"; ?>
--FILE--
<?php 
echo "wing_sharememory extension is available";
/*
	you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

	see php7/README.TESTING for further information on
  writing regression tests
*/
?>
--EXPECT--
wing_sharememory extension is available
