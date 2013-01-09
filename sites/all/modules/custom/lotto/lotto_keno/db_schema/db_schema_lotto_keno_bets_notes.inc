<?php
Function get_schema_lotto_keno_bets_notes(&$schema){
    $schema['lotto_keno_bets_notes'] = array(
      'description' => 'Add description',
      'fields' => array(
	'lkbnid' => array(
	  'description' => 'Add description',
	  'type' => 'serial',
	  'not null' => TRUE,
	),
	'lkbid' => array(
	  'description' => 'Add description',
	  'type' => 'int',
	  'not null' => FALSE,
	),
	'lkb_notes' => array(
	  'description' => 'Add description',
	  'type' => 'varchar',
	  'length' => '100',
	  'not null' => FALSE,
	),
      ),
      'primary key' => array('lkbnid'),
    );
}
?>
