<?php

Function get_schema_lotto_max(&$schema){
   $schema['lotto_max'] = array(
  'description' => 'TODO: please describe this table!',
  'fields' => array(
    'lmxid' => array(
      'description' => 'Add description',
      'type' => 'serial',
      'not null' => TRUE,
    ),
    'draw_number' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'draw_sequence' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'draw_date' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'n1' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'n2' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'n3' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'n4' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'n5' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'n6' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'n7' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'bn' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
  ),
  'primary key' => array('lmxid'),
);
 
}
?>
