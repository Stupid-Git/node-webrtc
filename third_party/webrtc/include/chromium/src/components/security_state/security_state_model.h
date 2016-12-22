// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SECURITY_STATE_SECURITY_STATE_MODEL_H_
#define COMPONENTS_SECURITY_STATE_SECURITY_STATE_MODEL_H_

#include <stdint.h>

#include "base/macros.h"
#include "net/cert/cert_status_flags.h"
#include "net/cert/sct_status_flags.h"
#include "net/cert/x509_certificate.h"
#include "url/gurl.h"

namespace security_state {

class SecurityStateModelClient;

// SecurityStateModel provides high-level security information about a
// page or request.
//
// SecurityStateModel::SecurityInfo is the main data structure computed
// by a SecurityStateModel. SecurityInfo contains a SecurityLevel (which
// is a single value describing the overall security state) along with
// information that a consumer might want to display in UI to explain or
// elaborate on the SecurityLevel.
class SecurityStateModel {
 public:
  // Describes the overall security state of the page.
  //
  // If you reorder, add, or delete values from this enum, you must also
  // update the UI icons in ToolbarModelImpl::GetIconForSecurityLevel.
  //
  // A Java counterpart will be generated for this enum.
  // GENERATED_JAVA_ENUM_PACKAGE: org.chromium.components.security_state
  // GENERATED_JAVA_CLASS_NAME_OVERRIDE: ConnectionSecurityLevel
  enum SecurityLevel {
    // HTTP/no URL/HTTPS but with insecure passive content on the page.
    NONE,

    // HTTP, in a case where we want to show a visible warning about the page's
    // lack of security.
    //
    // The criteria used to classify pages as NONE vs. HTTP_SHOW_WARNING will
    // change over time. Eventually, NONE will be eliminated.
    // See https://crbug.com/647754.
    HTTP_SHOW_WARNING,

    // HTTPS with valid EV cert.
    EV_SECURE,

    // HTTPS (non-EV) with valid cert.
    SECURE,

    // HTTPS, but with an outdated protocol version.
    SECURITY_WARNING,

    // HTTPS, but the certificate verification chain is anchored on a
    // certificate that was installed by the system administrator.
    SECURE_WITH_POLICY_INSTALLED_CERT,

    // Attempted HTTPS and failed, page not authenticated, HTTPS with
    // insecure active content on the page, malware, phishing, or any other
    // serious security issue that could be dangerous.
    DANGEROUS,
  };

  // Describes how the SHA1 deprecation policy applies to an HTTPS
  // connection.
  enum SHA1DeprecationStatus {
    UNKNOWN_SHA1,
    // No SHA1 deprecation policy applies.
    NO_DEPRECATED_SHA1,
    // The connection used a certificate with a SHA1 signature in the
    // chain, and policy says that the connection should be treated with a
    // warning.
    DEPRECATED_SHA1_MINOR,
    // The connection used a certificate with a SHA1 signature in the
    // chain, and policy says that the connection should be treated as
    // broken HTTPS.
    DEPRECATED_SHA1_MAJOR,
  };

  // The ContentStatus enum is used to describe content on the page that
  // has significantly different security properties than the main page
  // load. Content can be passive content that is displayed (such as
  // images) or active content that is run (such as scripts or iframes).
  enum ContentStatus {
    CONTENT_STATUS_UNKNOWN,
    CONTENT_STATUS_NONE,
    CONTENT_STATUS_DISPLAYED,
    CONTENT_STATUS_RAN,
    CONTENT_STATUS_DISPLAYED_AND_RAN,
  };

  // Describes the security status of a page or request. This is the
  // main data structure provided by this class.
  struct SecurityInfo {
    SecurityInfo();
    ~SecurityInfo();
    SecurityLevel security_level;
    // True if the page fails the browser's malware or phishing checks.
    bool fails_malware_check;
    SHA1DeprecationStatus sha1_deprecation_status;
    // |mixed_content_status| describes the presence of content that was
    // loaded over a nonsecure (HTTP) connection.
    ContentStatus mixed_content_status;
    // |content_with_cert_errors_status| describes the presence of
    // content that was loaded over an HTTPS connection with
    // certificate errors.
    ContentStatus content_with_cert_errors_status;
    // The verification statuses of the signed certificate timestamps
    // for the connection.
    std::vector<net::ct::SCTVerifyStatus> sct_verify_statuses;
    bool scheme_is_cryptographic;
    net::CertStatus cert_status;
    scoped_refptr<net::X509Certificate> certificate;
    // The security strength, in bits, of the SSL cipher suite. In late
    // 2015, 128 is considered the minimum.
    //
    // 0 means the connection uses HTTPS but is not encrypted.  -1 means
    // the security strength is unknown or the connection does not use
    // HTTPS.
    int security_bits;
    // Information about the SSL connection, such as protocol and
    // ciphersuite. See ssl_connection_flags.h in net.
    int connection_status;
    // The ID of the (EC)DH group used by the key exchange. The value is zero if
    // unknown (older cache entries may not store the value) or not applicable.
    uint16_t key_exchange_group;
    // A mask that indicates which of the protocol version,
    // key exchange, or cipher for the connection is considered
    // obsolete. See net::ObsoleteSSLMask for specific mask values.
    int obsolete_ssl_status;

    // True if pinning was bypassed due to a local trust anchor.
    bool pkp_bypassed;

    // True if the page displayed sensitive user data inputs (like a
    // password or credit card) on an HTTP page.
    bool displayed_private_user_data_input_on_http;
  };

  // Contains the security state relevant to computing the SecurityInfo
  // for a page. This is the input to GetSecurityInfo() provided by the
  // model's client.
  struct VisibleSecurityState {
    VisibleSecurityState();
    ~VisibleSecurityState();
    bool operator==(const VisibleSecurityState& other) const;
    GURL url;

    // True if the page fails the browser's malware or phishing checks.
    bool fails_malware_check;

    // CONNECTION SECURITY FIELDS
    // Whether the connection security fields are initialized.
    bool connection_info_initialized;
    // The following fields contain information about the connection
    // used to load the page or request.
    scoped_refptr<net::X509Certificate> certificate;
    net::CertStatus cert_status;
    int connection_status;
    // The ID of the (EC)DH group used by the key exchange. The value is zero if
    // unknown (older cache entries may not store the value) or not applicable.
    uint16_t key_exchange_group;
    int security_bits;
    // The verification statuses of the Signed Certificate
    // Timestamps (if any) that the server provided.
    std::vector<net::ct::SCTVerifyStatus> sct_verify_statuses;
    // True if the page displayed passive mixed content.
    bool displayed_mixed_content;
    // True if the page ran active mixed content.
    bool ran_mixed_content;
    // True if the page displayed passive subresources with certificate errors.
    bool displayed_content_with_cert_errors;
    // True if the page ran active subresources with certificate errors.
    bool ran_content_with_cert_errors;
    // True if PKP was bypassed due to a local trust anchor.
    bool pkp_bypassed;
    // True if the page was an HTTP page that displayed a password field.
    bool displayed_password_field_on_http;
    // True if the page was an HTTP page that displayed a credit card field.
    bool displayed_credit_card_field_on_http;
  };

  // These security levels describe the treatment given to pages that
  // display and run mixed content. They are used to coordinate the
  // treatment of mixed content with other security UI elements.
  static const SecurityLevel kDisplayedInsecureContentLevel;
  static const SecurityLevel kRanInsecureContentLevel;

  SecurityStateModel();
  virtual ~SecurityStateModel();

  // Populates |result| to describe the current page.
  void GetSecurityInfo(SecurityInfo* result) const;

  void SetClient(SecurityStateModelClient* client);

 private:
  SecurityStateModelClient* client_;

  DISALLOW_COPY_AND_ASSIGN(SecurityStateModel);
};

}  // namespace security_state

#endif  // COMPONENTS_SECURITY_STATE_SECURITY_STATE_MODEL_H_