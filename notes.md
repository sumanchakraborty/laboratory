-   [Notes, cautions, and warnings](#notes-cautions-and-warnings)
-   [Revision history](#revision-history)
-   [Product description](#product-description)
-   [New features and changes](#new-features-and-changes)
-   [Known problems and limitations](#known-problems-and-limitations)
    -   [Limitations](#limitations)
-   [Software media, organization, and
    files](#software-media-organization-and-files)
-   [Additional resources](#additional-resources)
    -   [Documentation](#documentation)
    -   [Troubleshoot and get help](#troubleshoot-and-get-help)
        -   [Technical support](#technical-support)

**Ansible Modules for Dell EMC PowerMax** Release Notes

**1.2**

Notes, cautions, and warnings
=============================

**NOTE:** A NOTE indicates important information that helps you make
better use of your product.

**CAUTION: A CAUTION indicates either potential damage to hardware or
loss of data and tells you how to avoid the problem.**

**WARNING: A WARNING indicates a potential for property damage, personal
injury, or death.**

© 2016 - 2020 Dell Inc. or its subsidiaries. All rights reserved. Dell,
EMC, and other trademarks are trademarks of Dell Inc. or its
subsidiaries. Other trademarks may be trademarks of their respective
owners.

**1**

**Release Notes**

These release notes contain supplemental information about Ansible
Modules for Dell EMC PowerMax. Topics include: **Topics:**

-   Revision history

-   Product description

-   New features and changes

-   Known problems and limitations

-   Software media, organization, and files

-   Additional resources

Revision history
================

| **Date**       | **Document revision** | **Description of changes**                        |
|----------------|-----------------------|---------------------------------------------------|
| September 2020 | 01                    | Ansible Modules for Dell EMC PowerMax release 1.2 |

Product description
===================

This section describes the Ansible Modules for Dell EMC PowerMax arrays.

The Ansible Modules for Dell EMC PowerMax are used for managing volumes,
storage groups, ports, port groups, host, host groups, masking views,
SRDF Links, RDF Groups, and snapshots for PowerMax arrays. The modules
use playbooks to list, show, create, delete, and modify each of the
entities.

The Ansible Modules for Dell EMC PowerMax supports the following
features:

-   Create volumes, storage groups, hosts, host groups, port groups,
    masking views, and snapshots of a storage group. ● Modify volumes,
    storage groups, hosts, host groups, and port groups in the array.

-   Delete volumes, storage groups, hosts, host groups, port groups,
    masking views, and snapshots of a storage group.

-   Get details of a port.

-   Get entities of the array.

New features and changes
========================

This section describes the new features of the Ansible Modules for Dell
EMC PowerMax in this release.

The Ansible Modules for Dell EMC PowerMax release 1.2 supports the
following features:

-   The following enhancements have been made in Storage Group module:

    1.  Add new volumes to SDRF protected storage group.

  ○ Remove volumes from SDRF protected storage group.

  **NOTE:** Add/ Remove volume to/from SRDF protected storage group is
  supported from PowerMax Foxtail version (v5978.444.444) onwards.

-   The following enhancements have been made in Volume module:

    1.  Add new volume to SDRF protected storage group.

  ○ Expand volume which is part of SRDF protected storage group.

  **NOTE:** Add/Expand volume to/from SRDF protected storage group is
  supported from PowerMax Foxtail version (v5978.444.444) onwards.

**Release Notes 3**

-   The SRDF Module supports the following functionalities for
    concurrent configuration: **NOTE:** See [SRDF
    documentation](https://www.dellemc.com/fi-fi/collaterals/unauth/technical-guides-support-information/products/storage/docu88915.pdf)
    for more details about SRDF functionality.

    1.  Create concurrent SRDF pair with the following replication
          modes:

  ￭ Synchronous

  ￭ Asynchronous

  ￭ Adaptive copy

  ￭ Active mode

  ○ Get SRDF pair states for a given storage group and RDFG number.

  ○ Modify concurrent SRDF pair mode. ○ Perform the following
  operations:

  ￭ Establish

  ￭ Restore ￭ Swap

  ￭ Failover

  ￭ Resume

  ￭ Suspend

  ￭ Split

  ￭ Failback

  ￭ Setbias

  ○ Delete concurrent SRDF pair.

-   Support for Unisphere 9.1 and above

-   Support for Python version 2.7 and above

-   Support for PyU4V python library version 9.1.0.0 and above

  **NOTE:** Unisphere Version 9.1 is compatible with PowerMax Python
  library version 9.1.x.x and similarly Unisphere version above 9.1 will
  only work with Python library version greater than 9.1.x.x.

-   Support for PowerMaxOS 5978.665.665

The following enhancements have been made in Gather Facts module:

-   Supports Health key to get the health status of PowerMax array.

-   Supports Generic filters that return a subset of storage entities.

-   Return section has been added for each module.

Known problems and limitations
==============================

This section lists the known problems and limitations of Ansible modules
for Dell EMC PowerMax.

● Known problems ● Limitations

**Known problems**

There are no known problems in this release.

Limitations
-----------

This section lists the limitations in this release of Ansible modules
for Dell EMC PowerMax.

-   Star and Cascaded multisite SRDF configurations are not supported.

-   The Invalidate, Ready, Not Ready, Move Pairs, and Refresh SRDF
      pairing operations are not supported. ● Migration use cases are
      not supported through the SRDF Module.

-   PyU4V v9.1 and above are supported in this release. ● PyU4V v3.x and
      Unisphere v9.0 are not supported.

**4 Release Notes**

Software media, organization, and files
=======================================

This section provides information about where to find the software files
for this release of the product.

The software package is available for download from the [Ansible Modules
for PowerMax GitHub](https://github.com/dell/ansible-powermax) page.

Additional resources
====================

This section provides more information about the product, how to get
support, and provide feedback.

Documentation
-------------

This section lists the related documentation for Ansible Modules for
Dell EMC PowerMax.

The Ansible Modules for Dell EMC PowerMax is available on [Ansible
Modules for PowerMax GitHub](https://github.com/dell/ansible-powermax)
page. The documentation includes the following:

● Ansible Modules for Dell EMC PowerMax Release Notes (this document) ●
Ansible Modules for Dell EMC PowerMax Product Guide

Troubleshoot and get help
-------------------------

Use the resources in this topic to get help and support.

### Technical support

Ansible modules for PowerStore are supported by Dell EMC, and are
provided under the terms of the license that is attached to the source
code. Dell EMC does not provide support for any source code
modifications.

For Ansible configuration, setup issues, or questions, use the [Dell EMC
Automation
community](https://www.dell.com/community/Automation/bd-p/Automation).
For any issues with Dell EMC Storage, contact [Dell EMC Online
Support](http://www.dell.com/support).

**Release Notes 5**
