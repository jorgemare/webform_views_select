<?php

/**
 * @file
 * Contains WebformViewsSelectStyle.
 */

/**
 * The style plugin for Webform Views Select.
 */
class WebformViewsSelectStyle extends views_plugin_style_mapping {

  /**
   * Implements views_plugin_style_mapping::define_mapping().
   */
  public function define_mapping() {
    return array(
      'webform_select_key' => array(
        '#title' => t('Select Key'),
        '#required' => TRUE,
      ),
      'webform_select_value' => array(
        '#title' => t('Select Value'),
        '#required' => TRUE,
      ),
    );
  }

  /**
   * Implements views_plugin_style::validate().
   */
  public function validate() {
    $errors = parent::validate();

    // The master display is of type 'default'.
    if ($this->display->display_plugin != 'webform_select' && $this->display->display_plugin != 'default') {
      $errors[] = t("%display: the 'Webform Select List' format requires a display of type 'Webform Options', but it is of type %displayplugin.", array('@style' => $this->definition['title'], '%displayplugin' => $this->display->handler->definition['title'], '%display' => $this->display->display_title));
    }
    return $errors;
  }

  /**
   * Implements views_plugin_style::render_grouping_sets().
   */
  public function render_grouping_sets($sets, $level = 0) {
    $key = $this->options['mapping']['webform_select_key'];
    $value = $this->options['mapping']['webform_select_value'];

    $output = array();
    foreach ($sets as $set) {
      // Render as a grouping set.
      if (is_array($set) && isset($set['group'])) {
        $row = reset($set['rows']);
        $output[htmlspecialchars_decode(strip_tags($set['group']))] = $this->render_grouping_sets($set['rows'], $level + 1);
      }
      // Render as a record set.
      else {
        $result = (array) $set;
        // We strip HTML tags from the field output because some fields (e.g.
        // Date fields) include tags in their output.
        $rendered_key = htmlspecialchars_decode(strip_tags($result[$key]), ENT_QUOTES);
        $rendered_value = htmlspecialchars_decode(strip_tags($result[$value]), ENT_QUOTES);
        $output[$rendered_key] = $rendered_value;
      }
    }

    return $output;
  }
}
