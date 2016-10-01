<?php

/**
 * @file
 * The file that contains the views_facetedsearch_plugin_style_facetedsearch class
 */

/**
 * This view plugin style inherits and overwrites the views_plugin_style class
 * with the functionality needed for Faceted Searches.
 */
class views_facetedsearch_plugin_style_facetedsearch extends views_plugin_style {
  /**
   * Safely add an option to the option form.
   * This means that if the option is unset it is set to null.
   *
   * @param array $form
   * @param string $type
   * @param string $facet_option_key
   * @param string $title
   * @param string $description
   */
  function safe_add_option(&$form, $type, $facet_option_key, $title, $description) {
    if (array_key_exists($facet_option_key, $this->options)) {
      $currentValue = $this->options[$facet_option_key];
    }
    else {
      $currentValue = NULL;
    }

    $form[$facet_option_key] = array(
      '#type' => $type,
      '#title' => t($title),
      '#default_value' => $currentValue,
    );

    if ($description != '') {
      $form[$facet_option_key]['#description'] = htmlentities($description);
    }
  }

  /**
   * Safely add an option from a field.
   *
   * @param array $form
   * @param string $prefix
   * @param array $each_selected_field
   * @param string $title
   */
  function safe_add_option_from_field(&$form, $prefix, $each_selected_field, $title) {
    $facet_option_key = $prefix . $each_selected_field['id'];

    if (array_key_exists('label', $each_selected_field)) {
      $optionTitle = t($each_selected_field['label']);
    }
    else {
      $optionTitle = t($each_selected_field['id']);
    }

    $this->safe_add_option($form, 'checkbox', $facet_option_key, $optionTitle, '');
  }

  /**
   * Add the needed options to the format's settings form.
   *
   * @param array $form
   * @param array $form_state
   */
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $selected_fields = $form_state['view']->display_handler->display->handler->view->
        display['default']->handler->view->display_handler->default_display->display->
        display_options['fields'];

    $form['views_facetedsearch_table'] = array(
      '#markup' => '<table>',
    );

    // Iterate through each field, putting its enable and allow order by option
    // into a table format.
    foreach ($selected_fields as $selected_field_key => $each_selected_field) {
      $form['views_facetedsearch_row_' . $selected_field_key] = array(
        '#markup' => '<tr><td>',
      );

      $this->safe_add_option_from_field($form, 'views_facetedsearch_facets_' , $each_selected_field, 'Allow searching by ');

      $form['views_facetedsearch_cell_separator_' . $selected_field_key] = array(
        '#markup' => '</td><td>',
      );

      $this->safe_add_option_from_field($form, 'views_facetedsearch_facetorders_' , $each_selected_field, 'Allow ordering by ');

      $form['views_facetedsearch_row_close_' . $selected_field_key] = array(
        '#markup' => '</td></tr>',
      );
    }

    $form['views_facetedsearch_table_close'] = array(
      '#markup' => '</table>',
    );

    // Add other one-off options here.
    $this->safe_add_option($form, 'checkbox', 'views_facetedsearch_enable_pagination',
        'Enable Pagination', 'Check box to allow pagination.');

    $this->safe_add_option($form, 'textfield', 'views_facetedsearch_pagination_count',
        'Results per Page', 'Enter the number of results initially shown.');

    $this->safe_add_option($form, 'textarea', 'views_facetedsearch_itemtemplate',
        'Item Template', 'This should be HTML that contains the keys of what you want to display in the form <%= obj.{field} %>, e.g. <%= obj.id %>.');

    $this->safe_add_option($form, 'textfield', 'views_facetedsearch_resultscontainer',
        'Results Container', 'This is the HTML element that the results appear in. It must have the id "view_facetedsearch_results". e.g. <div id="view_facetedsearch_results"></div>');
    
    $this->safe_add_option($form, 'textfield', 'views_facetedsearch_facetcontainer',
        'Facet Container', 'This is the HTML element that the filter options appear in. It must have the class "facetsearch" and an id variable. e.g. <div class="facetsearch" id=<%= id %> ></div>');
    
    $this->safe_add_option($form, 'textfield', 'views_facetedsearch_facetlistcontainer',
        'Facet List Container', 'This is the HTML element that the facet options appear in. It must have the class "facetlist". e.g. <div class="facetlist"></div>');
  }

  /**
   * Add the needed jQuery and render the fields.
   *
   * @return theme
   */
  function render() {
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/underscore-1.1.7.js');
    drupal_add_js(drupal_get_path('module', 'views_facetedsearch') . '/js/facetedsearch.js');

    parent::render();

    return theme($this->theme_functions(), array(
      'view' => $this->view,
      'options' => $this->options,
      'rows' => $this->render_fields($this->view->result), // Render_fields translates pseudoconstants.
    ));
  }
}