// swift-tools-version:4.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "Dgmpp",
    products: [
        // Products define the executables and libraries produced by a package, and make them visible to other packages.
        .library(
            name: "Dgmpp",
            targets: ["Dgmpp"]),
		
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages which this package depends on.
        .target(
            name: "Dgmpp",
			dependencies: ["cwrapper"],
			path: "swift-wrapper"
            ),
		.target(
			name: "cpp",
			path: "src",
			publicHeadersPath: ""
		),
		.target(
				name: "cwrapper",
				dependencies: ["cpp"],
				path: "c-wrapper"
		),
    ],
	cxxLanguageStandard: .gnucxx1z
)
