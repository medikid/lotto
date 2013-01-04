<?php

Function get_schema_lotto_patterns(&$schema){
    $schema['lotto_patterns'] = array(
  'description' => 'TODO: please describe this table!',
  'fields' => array(
    'lpid' => array(
      'description' => 'Add description',
      'type' => 'serial',
      'not null' => TRUE,
    ),
    'lottery_name' => array(
      'description' => 'Add description',
      'type' => 'text',
      'not null' => TRUE,
    ),
    'lottery_draw_num' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'num' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => TRUE,
    ),
    'diag_step_up' => array(
      'description' => 'Add description',
      'type' => 'varchar',
      'length' => '11',
      'not null' => FALSE,
    ),
    'pillar_down' => array(
      'description' => 'Add description',
      'type' => 'varchar',
      'length' => '11',
      'not null' => FALSE,
    ),
    'diag_step_down' => array(
      'description' => 'Add description',
      'type' => 'varchar',
      'length' => '11',
      'not null' => FALSE,
    ),
    'diag_und_step_up' => array(
      'description' => 'Add description',
      'type' => 'varchar',
      'length' => '11',
      'not null' => FALSE,
    ),
    'diag_und_step_down' => array(
      'description' => 'Add description',
      'type' => 'varchar',
      'length' => '11',
      'not null' => FALSE,
    ),
  ),
  'primary key' => array('lpid'),
);

}
?>
