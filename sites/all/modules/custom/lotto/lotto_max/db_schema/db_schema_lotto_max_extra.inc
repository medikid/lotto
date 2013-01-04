<?php

Function get_schema_lotto_max_extra(&$schema){
    $schema['lotto_max_extra'] = array(
  'description' => 'TODO: please describe this table!',
  'fields' => array(
    'lmxeid' => array(
      'description' => 'Add description',
      'type' => 'serial',
      'not null' => TRUE,
    ),
    'draw_number' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'draw_date' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'en1' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'en2' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'en3' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'en4' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
  ),
  'primary key' => array('lmxeid'),
);

}
?>
