<?php

function get_lotto_keno_patterns_diag_wins_review_form($form, &$form_state){
    $form = array();
    $form['diag_wins'] = array(
	'#type'=>'fieldset',
	'#title'=>t('Diag Winnings'),
	'#collapsible'=>true,
	'#collapsed'=>false
    );
    
    $form['diag_wins']['draw_number'] = array(
	'#type'=>'textfield',
	'#title'=>t('Draw Number: '),
	'#default_value'=>'',
	'#size'=>20,
	'#prefix'=>'<div class="container-inline">',
	'#suffix'=>'&nbsp &nbsp'
    );
    
    $form['diag_wins']['number_of_draws'] = array(
	'#type'=>'textfield',
	'#title'=>t('Number Of Draws to Review: '),
	'#default_value'=>'',
	'#size'=>5,
	'#suffix'=>'&nbsp &nbsp &nbsp &nbsp '
    );
    
    $form['diag_wins']['review_diag_wins'] = array(
	'#type'=>'button',
	'#value'=>t('Review'),
	'#ajax'=>array(
	    'callback' => 'ajx_keno_diag_wins_pattern',
	    'wrapper'=>'ajx_keno_diag_wins_pattern_wrapper',
	    'method'=>'replace'
	),
	'#suffix'=>'</div>'
    );
        
    
    $form['diag_wins']['diag_wins_pattern'] = array(
	'#markup'=>'',
	'#prefix'=>'<div id="ajx_keno_diag_wins_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    return $form;
}

function ajx_keno_diag_wins_pattern($form, $form_state){
    $diag_wins_pattern_grid = lotto_patterns_diag_win_pattern_grid_create('lotto_keno', $form_state['values']['draw_number'], $form_state['values']['number_of_draws'] );
    
    $form['diag_wins']['diag_wins_pattern']['#markup'] = $diag_wins_pattern_grid;
    
    return $form['diag_wins']['diag_wins_pattern'];
}

?>
