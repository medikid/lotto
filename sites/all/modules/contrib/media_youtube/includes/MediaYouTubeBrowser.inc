<?php

/**
 * @file media_youtube/includes/MediaYouTubeBrowser.inc
 *
 * Definition of MediaYouTubeBrowser.
 */

/**
 * Media browser plugin for displaying a specific view and display.
 */
class MediaYouTubeBrowser extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    // @todo Replace with file_access().
    return media_access('edit', $account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    // Check if the user is able to add remote media.
    if (user_access('add media from remote sources')) {
      $build['form'] = drupal_get_form('media_youtube_add', $this->params['types'], $this->params['multiselect']);
      return $build;
    }
  }
}
