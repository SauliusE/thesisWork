var NAVTREE =
[
  [ "My Project", "index.html", [
    [ "Lightweight Communications and Marshalling (LCM)", "index.html", [
      [ "Quick links", "index.html#main_quick_links", null ],
      [ "API Reference", "index.html#main_api_ref", null ]
    ] ],
    [ "Build Instructions", "build_instructions.html", [
      [ "Building a released version", "build_instructions.html#build_released", [
        [ "Ubuntu / Debian", "build_instructions.html#build_ubuntu_debian", null ],
        [ "OS X", "build_instructions.html#build_osx", [
          [ "MacPorts", "build_instructions.html#build_osx_macports", null ]
        ] ],
        [ "Windows", "build_instructions.html#build_windows", null ],
        [ "Other / General", "build_instructions.html#build_other", null ]
      ] ],
      [ "Building from Git", "build_instructions.html#build_git", [
        [ "Ubuntu / Debian", "build_instructions.html#build_git_ubuntu_debian", null ],
        [ "OS X", "build_instructions.html#build_git_osx", null ],
        [ "Windows", "build_instructions.html#build_git_windows", null ],
        [ "Other / General", "build_instructions.html#build_git_other", null ]
      ] ]
    ] ],
    [ "Java application notes", "java_notes.html", [
      [ "Finding lcm.jar", "java_notes.html#java_lcm_jar", null ],
      [ "Building lcm.jar separately from the rest of LCM", "java_notes.html#java_notes_separately", null ],
      [ "Namespace issues", "java_notes.html#tut_java_namespace", null ]
    ] ],
    [ "LCM Type Specification Language", "type_specification.html", [
      [ "Introduction", "type_specification.html#type_specification_intro", [
        [ "Design Goals", "type_specification.html#type_specification_design_goals", null ]
      ] ],
      [ "Type Specifications", "type_specification.html#type_specification_spec", [
        [ "Structs", "type_specification.html#type_specification_structs", null ],
        [ "Constants", "type_specification.html#type_specification_constants", null ]
      ] ],
      [ "Namespaces", "type_specification.html#type_specification_namespaces", null ],
      [ "Performance Considerations", "type_specification.html#type_specification_performance", null ],
      [ "Fingerprint Computation", "type_specification.html#type_specification_fingerprints", [
        [ "Related Work", "type_specification.html#type_specification_related_work", null ],
        [ "Development History", "type_specification.html#type_specification_history", null ]
      ] ]
    ] ],
    [ "LCM Log File format", "log_file_format.html", null ],
    [ "The Lua LCM API", "lua_api.html", [
      [ "LCM Userdata", "lua_api.html#lcm_userdata", [
        [ "new", "lua_api.html#lcm_userdata_new", null ],
        [ "publish", "lua_api.html#lcm_userdata_publish", null ],
        [ "subscribe", "lua_api.html#lcm_userdata_subscribe", null ],
        [ "unsubscribe", "lua_api.html#lcm_userdata_unsubscribe", null ],
        [ "handle", "lua_api.html#lcm_userdata_handle", null ],
        [ "handle_timeout", "lua_api.html#lcm_userdata_handle_timeout", null ],
        [ "timedhandle (Deprecated)", "lua_api.html#lcm_userdata_timedhandle", null ]
      ] ]
    ] ],
    [ "UDP Multicast Setup", "multicast_setup.html", [
      [ "Using LCM on a single host", "multicast_setup.html#multicast_single_host", null ],
      [ "Using LCM across multiple hosts", "multicast_setup.html#multicast_multihost", [
        [ "Choosing a TTL", "multicast_setup.html#multicast_ttl", null ],
        [ "Using IGMP snooping", "multicast_setup.html#multicast_igmp", null ],
        [ "Firewalls", "multicast_setup.html#multicast_firewalls", null ],
        [ "Mixed-speed networks", "multicast_setup.html#multicast_mixed_speed", null ]
      ] ],
      [ "Kernel UDP receive buffer sizing", "multicast_setup.html#multicast_kernel_buffer", null ]
    ] ],
    [ "C Tutorial", "tutorial_c.html", [
      [ "Introduction", "tutorial_c.html#tutorial_c_intro", null ],
      [ "Initializing LCM", "tutorial_c.html#tutorial_c_initialize", null ],
      [ "Publishing a message", "tutorial_c.html#tutorial_c_publishing", null ],
      [ "Receiving LCM Messages", "tutorial_c.html#tutorial_c_receive", null ]
    ] ],
    [ "C++ Tutorial", "tut_cpp.html", [
      [ "Introduction", "tut_cpp.html#tut_cpp_intro", null ],
      [ "Initializing LCM", "tut_cpp.html#tut_cpp_initialize", null ],
      [ "Publishing a message", "tut_cpp.html#tut_cpp_publishing", null ],
      [ "Receiving LCM Messages", "tut_cpp.html#tut_cpp_receive", null ]
    ] ],
    [ ".NET Tutorial", "tut_dotnet.html", [
      [ "C#.NET-specific message files", "tut_dotnet.html#Generating", null ],
      [ "Introduction", "tut_dotnet.html#tut_dotnet_intro", null ],
      [ "Initializing LCM", "tut_dotnet.html#tut_dotnet_initialize", null ],
      [ "Publishing a message", "tut_dotnet.html#tut_dotnet_publish", null ],
      [ "Subscribing to messages", "tut_dotnet.html#tut_dotnet_subscribe", null ],
      [ "Putting it all together", "tut_dotnet.html#tut_dotnet_together", null ],
      [ "Conclusion", "tut_dotnet.html#tut_dotnet_conclusion", null ]
    ] ],
    [ "Java Tutorial", "tut_java.html", [
      [ "Introduction", "tut_java.html#tut_java_intro", null ],
      [ "Initializing LCM", "tut_java.html#tut_java_initialize", null ],
      [ "Publishing a message", "tut_java.html#tut_java_publish", null ],
      [ "Subscribing to messages", "tut_java.html#tut_java_subscribe", [
        [ "Putting it all together", "tut_java.html#tut_java_together", null ]
      ] ],
      [ "Compiling and running", "tut_java.html#tut_java_compiling_running", null ],
      [ "Additional notes", "tut_java.html#tut_java_notes", null ]
    ] ],
    [ "Defining a data type - \\c example_t", "tut_lcmgen.html", [
      [ "Generating language-specific bindings", "tut_lcmgen.html#tutorial_general_lcmgen", null ]
    ] ],
    [ "Lua Tutorial", "tut_lua.html", [
      [ "Introduction", "tut_lua.html#tut_lua_intro", null ],
      [ "Initializing LCM", "tut_lua.html#tut_lua_initialize", null ],
      [ "Publishing a message", "tut_lua.html#tut_lua_publishing", null ],
      [ "Receiving LCM Messages", "tut_lua.html#tut_lua_receive", null ]
    ] ],
    [ "MATLAB Tutorial", "tut_matlab.html", [
      [ "Introduction", "tut_matlab.html#tut_matlab_intro", null ],
      [ "Setting up MATLAB to use LCM", "tut_matlab.html#tut_matlab_setup", null ],
      [ "Initializing LCM", "tut_matlab.html#tut_matlab_initialize", null ],
      [ "Publishing a message", "tut_matlab.html#tut_matlab_publishing", null ],
      [ "Receiving LCM Messages", "tut_matlab.html#tut_matlab_receive", null ]
    ] ],
    [ "Python Tutorial", "tut_python.html", [
      [ "Introduction", "tut_python.html#tut_python_intro", null ],
      [ "Initializing LCM", "tut_python.html#tut_python_initialize", null ],
      [ "Publishing a message", "tut_python.html#tut_python_publishing", null ],
      [ "Receiving LCM Messages", "tut_python.html#tut_python_receive", null ]
    ] ],
    [ "Tutorial and examples", "tutorial_general.html", [
      [ "Introduction", "tutorial_general.html#tutorial_general_intro", null ]
    ] ],
    [ "LCM UDP Multicast Protocol Description", "udp_multicast_protocol.html", null ],
    [ "object related functions.", "_hash.html", null ],
    [ "object related functions.", "_l_c_m.html", null ],
    [ "Todo List", "todo.html", null ],
    [ "Deprecated List", "deprecated.html", null ],
    [ "Modules", "modules.html", "modules" ],
    [ "Namespaces", null, [
      [ "Namespace List", "namespaces.html", "namespaces" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", "namespacemembers_dup" ],
        [ "Functions", "namespacemembers_func.html", "namespacemembers_func" ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ],
        [ "Enumerator", "namespacemembers_eval.html", null ]
      ] ]
    ] ],
    [ "Classes", null, [
      [ "Class List", "annotated.html", "annotated" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ],
        [ "Properties", "functions_prop.html", null ],
        [ "Related Functions", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", null, [
      [ "File List", "files.html", "files" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", "globals_defs" ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_a_annotation_content_component_8java.html",
"_matcher_assert_8java.html",
"_win_porting_8h.html#a2c098a3733c4fbf44e603ede9dffc4e0",
"class_l_c_m_types_1_1temperature__t.html#a03885b673bd0912c1ea5007f7202d1cc",
"classinfo_1_1monitorenter_1_1gui_1_1chart_1_1_labeled_value.html#ac10a985896697498bbf8f647493c46fe",
"classinfo_1_1monitorenter_1_1gui_1_1chart_1_1axis_1_1_a_axis.html#a37591a45420703507793c7be2f3fb14c",
"classinfo_1_1monitorenter_1_1gui_1_1chart_1_1controls_1_1_layout_factory.html#a61de288925ebe7b86fe51078e5b6b1bf",
"classinfo_1_1monitorenter_1_1gui_1_1chart_1_1errorbars_1_1_error_bar_policy_relative.html#a4e3051d6660e4514fa99df6f2bbe3886",
"classinfo_1_1monitorenter_1_1gui_1_1chart_1_1io_1_1_property_file_static_data_collector.html#a65d49de25c995a112da38dd6924b5f80",
"classinfo_1_1monitorenter_1_1gui_1_1chart_1_1traces_1_1_a_trace2_d.html#a1211b93b403889cdd49e18fd66871762",
"classinfo_1_1monitorenter_1_1gui_1_1chart_1_1traces_1_1_trace2_d_ltd_sorted.html#a5f5f29857651127a2287df962a71e0f9",
"classinfo_1_1monitorenter_1_1util_1_1_time_stamped_value.html#afac91cb9145a37bfce885a005c18d4fa",
"classjunit_1_1framework_1_1_test_result.html#ac12315b42bca2a909a275aab375d18a0",
"classlcm_1_1logging_1_1_j_scrubber.html#a9e33fe92d40883a0a5005901d019a2d9",
"classlcmtest_1_1bools__t.html#a8b705fe3be1cb1d4ea08f5dd6aba5840",
"classorg_1_1hamcrest_1_1_type_safe_matcher.html#aa83240cd555e3e76f033924a1e389048",
"classorg_1_1junit_1_1internal_1_1matchers_1_1_type_safe_matcher.html#ac33294ee21390fed9a074db6ae298714",
"classorg_1_1junit_1_1runner_1_1notification_1_1_run_notifier.html#ab13a9b0be70ea3c8772850b3cc365041",
"classtesting_1_1_test_event_listeners.html#a9867c9af50e8d2934a2475286c7cebc5",
"classtesting_1_1internal_1_1_test_factory_base.html#a18f22a7594336a36642289c1decddc9e",
"common_8hpp.html#a5348d2fe74d3718697cbedaa033eaabd",
"emit__lua_8c.html#a741918ef15310510260893ce2f9b5d23",
"group___lcm_c__lcm__eventlog__t.html#ga12173edb1ed47ea85a6d97843b4efbc9",
"gtest-port_8h.html#a4042201dcc4932641d484e7ddf94de7d",
"gtest_8cc.html#a51fb68302e8e3fce5bd61340843a6e6a",
"interfaceinfo_1_1monitorenter_1_1gui_1_1chart_1_1_i_axis.html#a0d2df7fe2973b9849c9ee8cc06466594",
"interfaceinfo_1_1monitorenter_1_1gui_1_1chart_1_1_i_trace_point2_d.html#aeb82e6be76b6f37bbac33e80ec1beb7e",
"inttypes_8h.html#a9bc6b517c0117327e832824ff2d6a6b5",
"lcm__mpudpm_8c.html#acedc48d8b9e0314942811781b9c5b1ff",
"lcmtest__comments__t_8c.html#aff69a877a375acb1d35c411cd965cfcb",
"listener__select_8py.html#a4fa52fc68010f8301ab46d70b98b1b1a",
"namespacemembers_func_f.html",
"setup_8py.html#aecadf977b83530d9acda728db80eb0e8",
"struct__lcm__subscription__t.html",
"structlcmgen.html",
"tut_python.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';