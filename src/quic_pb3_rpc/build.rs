fn main() {
    println!("cargo:rerun-if-changed=src/bidirectional.proto");
    tonic_build::configure()
        .type_attribute(".", "#[derive(serde::Serialize, serde::Deserialize)]")
        .compile_well_known_types(true)
        .compile(&["src/bidirectional.proto"], &["proto"])
        .unwrap();
}