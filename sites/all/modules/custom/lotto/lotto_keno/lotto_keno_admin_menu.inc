<?php

function lotto_keno_menu(){
    $items=array();


        $items['admin/lotto/lottokeno'] = array(
        'title' => 'Lotto Keno',
        'description' => 'Lotto Keno',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('my_admin_function'),
        'access arguments' => array('administer site configuration'),
        );
	/********************************CHARTS*************************************************/
        $items['admin/lotto/lottokeno/charts'] = array(
        'title' => 'Charts',
        'description' => 'Get charts',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_charts_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	/********************************BETS*************************************************/
	$items['admin/lotto/lottokeno/bets'] = array(
        'title' => 'Bets',
        'description' => 'Bets',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_bets_review_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/review'] = array(
        'title' => 'Review',
        'description' => 'Review Bets',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_bets_review_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/autopicks'] = array(
        'title' => 'Autopicks',
        'description' => 'Autopicks',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_autopicks_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/autopicks/efficiency'] = array(
        'title' => 'Efficiency',
        'description' => 'Review Autopicks Efficiency',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_autopicks_efficiency_form'),
	//'page callback' => 'get_lotto_keno_autopicks_efficiency_form',
        //'page arguments' => array('draw_num'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/autopicks/numbersefficiency'] = array(
        'title' => 'Numbers Efficiency',
        'description' => 'Review Autopicks Efficiency',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_autopicks_numbers_efficiency_form'),
	//'page callback' => 'get_lotto_keno_autopicks_efficiency_form',
        //'page arguments' => array('draw_num'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/autopicks/numbersefficiency_t'] = array(
        'title' => 'Numbers Efficiency_t',
        'description' => 'Review Autopicks Efficiency',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_autopicks_numbers_efficiency_form_t'),
	//'page callback' => 'get_lotto_keno_autopicks_efficiency_form',
        //'page arguments' => array('draw_num'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/autopicks/efficiency_t'] = array(
        'title' => 'Efficiency_t',
        'description' => 'Review Autopicks Efficiency',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_autopicks_efficiency_form_t'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/autopicks/efficiencyreport'] = array(
        'title' => 'Efficiency Report',
        'description' => 'Autopicks Efficiency Report',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_autopicks_efficiency_report_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/bets/diagwins'] = array(
        'title' => 'Bets from Diag Wins Pattern',
        'description' => 'Review Bets',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_bets_diag_wins_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	/********************************RESULTS*************************************************/
	$items['admin/lotto/lottokeno/results'] = array(
        'title' => 'Results',
        'description' => 'Get Results',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_results_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/results/sync'] = array(
        'title' => 'Sync Online',
        'description' => 'Sync Results with bclc',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_results_sync_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	$items['admin/lotto/lottokeno/results/pattern'] = array(
        'title' => 'Patterns',
        'description' => 'View results trend',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_results_pattern_form'),
        'access arguments' => array('Access Lotto Keno Charts'),
        );
	
	$items['admin/lotto/lottokeno/results/pattern/diagwins'] = array(
        'title' => 'Diag Wins',
        'description' => 'Diag Wins Pattern trend',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_patterns_diag_wins_review_form'),
        'access arguments' => array('Access Lotto Keno Charts'),
        );
	
	$items['admin/lotto/lottokeno/results/analysis'] = array(
        'title' => 'Analysis',
        'description' => 'Analyze results',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('get_lotto_keno_results_analysis_form'),
        'access arguments' => array('Access Lotto Max Charts'),
        );
	
	return $items;
}
?>
