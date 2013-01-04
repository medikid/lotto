<?php

function get_schema_lotto_prize_table(&$schema){
$schema['lotto_prize_table'] = array(
  'description' => 'Add description',
  'fields' => array(
    'lptid' => array(
      'description' => 'Add description',
      'type' => 'serial',
      'not null' => TRUE,
    ),
    'lottery_name' => array(
      'description' => 'Add description',
      'type' => 'varchar',
      'length' => '20',
      'not null' => TRUE,
    ),
    'picks' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'matches' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'bonus' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'win' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
  ),
  'primary key' => array('lptid'),
);   
    
}
?>
