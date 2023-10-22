import http from "k6/http";

import { check } from "k6";

import { parseHTML } from "k6/html";

import { url } from "./config.js";

const testImage = open("testimage.jpg","b");

export default function () {
        const res = http.post(url("/login"), {
                account_name: 'terra',
                password: 'terraterra',
        });
        check(res, {
                "is status 200": (r) => r.status === 200,
        });

        const doc = parseHTML(res.body);
        const token = doc.find('input[name="csrf_token"]').first().attr("value");

        const postimage_res = http.post(url("/"), {
                file: http.file(testImage, "testimage.jpg","image/jpeg"),
                body: "Posted by k6",
                csrf_token: token,
        });
        check(postimage_res, {
                "is status 200": (r) => r.status === 200,
        });
}
