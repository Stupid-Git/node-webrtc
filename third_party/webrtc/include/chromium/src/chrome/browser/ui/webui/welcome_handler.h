// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_WELCOME_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_WELCOME_HANDLER_H_

#include "base/macros.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "google_apis/gaia/oauth2_token_service.h"

class Browser;
class Profile;
class ProfileOAuth2TokenService;

// Handles actions on Welcome page.
class WelcomeHandler : public content::WebUIMessageHandler,
                       public OAuth2TokenService::Observer {
 public:
  explicit WelcomeHandler(content::WebUI* web_ui);
  ~WelcomeHandler() override;

  // OAuth2TokenService::Observer:
  void OnRefreshTokenAvailable(const std::string& account_id) override;

  // content::WebUIMessageHandler:
  void RegisterMessages() override;

 private:
  enum WelcomeResult {
    DEFAULT = 0,    // User navigated away from the page.
    DECLINED = 1,   // User clicked the "No Thanks" button.
    SIGNED_IN = 2,  // User clicked the "Sign In" button and completed sign-in.

    // New results must be added before this line, and should correspond to
    // values in tools/metrics/histograms/histograms.xml.
    WELCOME_RESULT_MAX
  };

  void HandleActivateSignIn(const base::ListValue* args);
  void HandleUserDecline(const base::ListValue* args);
  void GoToNewTabPage();

  Browser* GetBrowser();

  Profile* profile_;
  ProfileOAuth2TokenService* oauth2_token_service_;
  WelcomeResult result_;

  DISALLOW_COPY_AND_ASSIGN(WelcomeHandler);
};

#endif  // CHROME_BROWSER_UI_WEBUI_WELCOME_HANDLER_H_