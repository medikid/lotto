<?php

Function get_schema_lotto_keno_bets(&$schema){
    $schema['lotto_keno_bets'] = array(
  'description' => 'TODO: please describe this table!',
  'fields' => array(
    'lkbid' => array(
      'description' => 'Add description',
      'type' => 'serial',
      'not null' => TRUE,
    ),
    'uid' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'draw_number' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'live_bets_flag' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
      'default' => 0,
    ),
    'live_bets_done' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
      'default' => 0,
    ),
    'pattern_type' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'picks' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'matches' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'wager' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'win' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b1' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b2' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b3' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b4' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b5' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b6' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b7' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b8' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b9' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'b10' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
    'bonus' => array(
      'description' => 'Add description',
      'type' => 'int',
      'not null' => FALSE,
    ),
  ),
  'primary key' => array('lkbid'),
);

}
?>
