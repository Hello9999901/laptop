import { defineConfig } from "astro/config";
import mdx from "@astrojs/mdx";
import sitemap from "@astrojs/sitemap";
import tailwind from "@astrojs/tailwind";
import solidJs from "@astrojs/solid-js";
import markdownIntegration from "@astropub/md";
import vercel from "@astrojs/vercel/static";
import { targetBlank } from './src/plugins/targetBlank';

// https://astro.build/config
export default defineConfig({
	site: "https://byran.ee",
	integrations: [
		mdx(),
		sitemap(),
		solidJs(),
		markdownIntegration(),
		tailwind({
			applyBaseStyles: false,
		}),
	],
	markdown: {
		remarkPlugins: [],
		rehypePlugins: [[targetBlank, { domain: 'byran.ee' }]],
		// syntaxHighlight: 'shiki'
		// syntaxHighlight: 'prism'
	},
	output: "static",
	adapter: vercel({
		webAnalytics: {
			enabled: true,
		},
	}),
});
