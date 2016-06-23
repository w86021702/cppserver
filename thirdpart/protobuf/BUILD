#link_protobuf_cmd='if [[ -e %s/%s/libprotobuf.so && -d %s/solib/ ]]; then ln -sf %s/%s/libprotobuf.so %s/solib/; fi'%(WORK_DIR(),OUT_DIR(),WORK_DIR(),WORK_DIR(),OUT_DIR(),WORK_DIR())
cc_library(
    name = 'protobuf',
    prebuilt = True,
    deps = [
        
    ],
    export_incs = [ 'src/google/protobuf',],
   # postaction = link_protobuf_cmd,
)

