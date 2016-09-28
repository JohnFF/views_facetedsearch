<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class views_facetedsearch_plugin_style_facetedsearch extends views_plugin_style {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function safe_add_option(&$form, $type, $facetOptionKey, $title, $description){
    if (array_key_exists($facetOptionKey, $this->options)){
      $currentValue = $this->options[$facetOptionKey];
    }
    else {
      $currentValue = NULL;
    }

    $form[$facetOptionKey] = array(
      '#type' => $type,
      '#title' => t($title),
      '#default_value' => $currentValue,
    );
    if ($description != ''){
      $form[$facetOptionKey]['#description'] = $description;
    }
  }

  function safe_add_option_from_field(&$form, $prefix, $eachSelectedField, $title){
    $facetOptionKey = $prefix . $eachSelectedField['field'];

    if (array_key_exists('label', $eachSelectedField)){
      $optionTitle = t($eachSelectedField['label']);
    }
    else {
      $optionTitle = t($eachSelectedField['id']);
    }

    $this->safe_add_option($form, 'checkbox', $facetOptionKey, $optionTitle, '');
  }

  // Build the settings form for the view.
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $selectedFields = $form_state['view']->display_handler->display->handler->view->
        display['default']->handler->view->display_handler->default_display->display->
        display_options['fields'];

    $form['views_facetedsearch_table'] = array(
      '#markup' => '<table>',
    );

    foreach($selectedFields as $selectedFieldKey => $eachSelectedField){

      $form['views_facetedsearch_row_' . $selectedFieldKey] = array(
        '#markup' => '<tr><td>',
      );

      $this->safe_add_option_from_field($form, 'views_facetedsearch_facets_' , $eachSelectedField, 'Allow searching by ');

      $form['views_facetedsearch_cell_separator_' . $selectedFieldKey] = array(
        '#markup' => '</td><td>',
      );

      $this->safe_add_option_from_field($form, 'views_facetedsearch_facetorders_' , $eachSelectedField, 'Allow ordering by ');

      $form['views_facetedsearch_row_close_' . $selectedFieldKey] = array(
        '#markup' => '</td></tr>',
      );
    }

    $form['views_facetedsearch_table_close'] = array(
      '#markup' => '</table>',
    );

    $this->safe_add_option($form, 'checkbox', 'views_facetedsearch_enable_pagination',
        'Enable Pagination', 'Check box to allow pagination.');

    $this->safe_add_option($form, 'textfield', 'views_facetedsearch_pagination_count',
        'Results per Page', 'Enter the number of results initially shown.');

/*    $this->safe_add_option($form, 'textarea', 'views_facetedsearch_item_template',
        'Item Template', 'Check box to display allow searching by facet.');*/
  }

  function render(){
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/underscore-1.1.7.js');
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/facetedsearch.js');

//    die(print_r(debug_print_backtrace(), TRUE));
    //print '<pre>' . print_r(debug_backtrace(), TRUE) . '</pre>';
    parent::render();

    //die(print_r($this->render_fields($this->view->result), TRUE));

    return theme($this->theme_functions(), array(
      'view' => $this->view,
      'options' => $this->options,
'rows' => $this->render_fields($this->view->result)
//'rows' => $this->view->result,
  //    'mapping' => $this->define_mapping(),
    ));
  }
}