<?php // $Id$

/**
 * An AHAH callback for the postal element.
 */
function postal_ahah_js() {
  // This hack ensures that node forms will work.  YMMV for other forms!
  if (substr($_POST['form_id'], -9) == 'node_form') {
    module_load_include('inc', 'node', 'node.pages');
  }

  //$form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_state = array('storage' => NULL, 'submitted' => FALSE, 'rebuild' => TRUE);
  $form_build_id = $_POST['form_build_id'];
  // Step #4.
  $form = form_get_cache($form_build_id, $form_state);

  // Preparing for #5.
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  // Step #5.
  drupal_process_form($form_id, $form, $form_state);

  // Step #6 and #7 and #8.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  // Clear out the form_errors array.  We're not here for validation.
  drupal_get_messages('error', TRUE);

  // Get the #array_parents value that was passed in to locate the element.
  $parents = func_get_args();
  foreach ($parents as $key) {
    if (isset($form[$key])) $form = $form[$key];
  }
  drupal_render($form);

  //$output = theme('status_messages') . drupal_render($form);
  $output = theme('status_messages') . $form['#children'];

  // Final rendering callback.
  drupal_json(array('status' => TRUE, 'data' => $output));
}
